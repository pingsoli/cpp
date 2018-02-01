/*
 * The order of linking library may occurs some errors ?
 * fiber -> context -> thread -> pthread
 * ------------------------------------>
 * high level                  low level
 *
 * Does that mean boost_context depend on boost_thread ?
 */
#include <cassert>
#include <chrono>
#include <exception>
#include <iostream>
#include <sstream>
#include <thread>
#include <tuple>

#include <boost/context/detail/apply.hpp>
#include <boost/fiber/all.hpp>

#if defined(BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES)

// helper code to help callback
template <typename Fn, typename ... Args>
class helper {
private:
  typename std::decay<Fn>::type                   fn_;
  std::tuple<typename std::decay<Args>::type ...> args_;

public:
  helper(Fn && fn, Args && ...args) :
    fn_(std::forward<Fn>(fn)),
    args_(std::make_tuple(std::forward<Args>(args)...))
  {}

  helper(helper && other)           = default;
  helper& operator=(helper const&&) = default;
  helper(helper const&)             = default;
  helper& operator=(helper const&)  = default;

  void operator()() {
    boost::context::detail::apply(fn_, args_);
  }
};

template <typename Fn, typename ... Args>
helper<Fn, Args...> help(Fn&& fn, Args&& ... args) {
  return helper<Fn, Args...>(std::forward<Fn>(fn),
                             std::forward<Args>(args)...);
}
#endif

class AsyncAPI {
public:
  AsyncAPI();

  typedef int errorcode;

  template<typename Fn>
  void init_write(std::string const& data, Fn && callback);

  template<typename Fn>
  void init_read(Fn&& callback);

  void inject_error(errorcode ec);

private:
  std::string data_;
  errorcode   injected_;
};

AsyncAPI::AsyncAPI() :
  injected_{0}
{}

void AsyncAPI::inject_error(errorcode ec) {
  injected_ = ec;
}

template<typename Fn>
void AsyncAPI::init_write(std::string const& data, Fn && callback)
{
  // make a copy of injected_
  errorcode injected{injected_};
  // reset it synchronously with caller
  injected_ = 0;

  // upate data_
  if (!injected_) {
    data_ = data;
  }

// Simulate an asynchronous I/O operation by lanuching a detached thread
// that sleeps a bit before calling completion callback, Echo back to
// caller any previously-injected errorcode
#if ! defined(BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES)
  std::thread(
    [injected, callback=std::forward<Fn>(callback), data]() mutable {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      callback(injected);
    }).detach();
#else
  std::thread(
    std::move(
      help(std::forward<Fn>(callback), injected, data)
    )).detach();
#endif
}

template <typename Fn>
void AsyncAPI::init_read(Fn && callback)
{
  // make a local copy of injected_
  errorcode injected{injected_};
  injected_ = 0;

  std::string data(data_);

#if ! defined(BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES)
  std::thread(
    [injected, callback=std::forward<Fn>(callback), data]() mutable {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      callback(injected, data);
    }).detach();
#else
    std::tread(
      std::move(
        help(std:forward<Fn>(callback), injected, data)
    )).detach();
#endif
}

// helper function used in a couple of the adapters
std::runtime_error
make_exception(std::string const& desc, AsyncAPI::errorcode);

AsyncAPI::errorcode write_ec(AsyncAPI& api, std::string const& data) {
  boost::fibers::promise<AsyncAPI::errorcode> promise;
  boost::fibers::future<AsyncAPI::errorcode> future(promise.get_future());

#if !defined(BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES)
  api.init_write(
    data,
    [promise=std::move(promise)](AsyncAPI::errorcode ec) mutable {
      promise.set_value(ec);
    });
#else
  api.init_write(
    data,
    std::bind([](boost::fibers::promise<AsyncAPI::errorcode> & promise,
        AsyncAPI::errorcode ec) {
        promise.set_value(ec);
      },
      std::move(promise),
      std::placeholders::_1));
#endif
  return future.get();
}

void write(AsyncAPI& api, std::string const& data) {
  AsyncAPI::errorcode ec = write_ec(api, data);
  if (ec) {
    throw make_exception("write", ec);
  }
}

std::pair<AsyncAPI::errorcode, std::string> read_ec(AsyncAPI & api) {
  typedef std::pair<AsyncAPI::errorcode, std::string> result_pair;
  boost::fibers::promise<result_pair> promise;
  boost::fibers::future<result_pair> future(promise.get_future());

#if !defined(BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES)
  api.init_read(
    [promise=std::move(promise)] (AsyncAPI::errorcode ec,
     std::string const &data) mutable
    {
      promise.set_value(result_pair(ec, data));
    }
  );
#else // defined(BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES)
  api.init_read(
    std::bind(
      [](boost::fibers::promise<result_pair>& promise,
        AsyncAPI::errorcode ec, std::string const &data) mutable
      {
        promise.set_value(result_pair(ec, data));
      },
      std::move(promise),
      std::placeholders::_1,
      std::placeholders::_2
    )
  );
#endif // BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES

  return future.get();
}

std::string read(AsyncAPI& api) {
  boost::fibers::promise<std::string> promise;
  boost::fibers::future<std::string> future(promise.get_future());

#if !defined(BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES)
  api.init_read(
    [&promise](AsyncAPI::errorcode ec, std::string const& data) mutable {
      if (!ec) {
        promise.set_value(data);
      } else {
        promise.set_exception(
          std::make_exception_ptr(make_exception("read", ec))
        );
      }
    });
#else
  api.init_read(
    std::bind(
      [](boost::fibers::promise<std::string> & promise,
        AsyncAPI::errorcode ec, std::string const& data) mutable {
          if (!ec) {
            promise.set_value(data);
          } else {
            promise.set_exception(
              std::make_exception_ptr(make_exception("read", ec))
            );
          }
      },
      std::move(promise),
      std::placeholders::_1,
      std::placeholders::_2
    ));
#endif
  return future.get();
}

std::runtime_error
make_exception(std::string const& desc, AsyncAPI::errorcode ec)
{
  std::ostringstream buffer;
  buffer << "Error in AsyncAPI::" << desc << "(): " << ec;
  return std::runtime_error(buffer.str());
}

/*
 * Make clear of what happing ?
 */
int main(int argc, char** argv)
{
  AsyncAPI api;

  write(api, "abcd");
  std::string data(read(api));
  assert(data == "abcd");
  std::cout << "Test1: " << data << '\n';

  AsyncAPI::errorcode ec(write_ec(api, "efgh"));
  std::cout << "write ec, api" << ec << '\n';
  assert(ec == 0);

  api.inject_error(1);
  ec = write_ec(api, "ijkl");
  assert(ec == 1);

  std::string thrown;
  api.inject_error(2);
  try {
    write(api, "mnop");
  } catch (std::exception const& e) {
    thrown = e.what();
  }
  assert(thrown == make_exception("write", 2).what());

  api.inject_error(3);
  std::tie(ec, data) = read_ec(api);
  assert(ec == 3);

  thrown.clear();
  api.inject_error(4);
  try {
    data = read(api);
  } catch (std::exception const& e) {
    thrown = e.what();
  }
  assert(thrown == make_exception("read", 4).what());

  std::cout << "done." << std::endl;

  return 0;
}
