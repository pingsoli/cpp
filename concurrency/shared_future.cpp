///////////////////////////////////////////////////////////////////////////////
//
// shared_future
// could invoke get() multiple times, shared by other futures
//
///////////////////////////////////////////////////////////////////////////////

#include <exception>
#include <future>
#include <iostream>
#include <thread>

std::mutex cout_mutex;

struct Div {
  void operator()(std::promise<int>&& int_promise, int a, int b) {
    try {
      if (0 == b)
        throw std::runtime_error("illegal division by zero");
      int_promise.set_value(a/b);
    } catch (...) {
      int_promise.set_exception(std::current_exception());
    }
  }
};

struct Requestor {
  void operator()(std::shared_future<int> sha_fut) {
    std::lock_guard<std::mutex> cout_guard(cout_mutex);

    std::cout << "thread id(" << std::this_thread::get_id() << "): ";

    try {
      std::cout << "20/10 = " << sha_fut.get() << std::endl;
    } catch (const std::runtime_error& e) {
      std::cout << e.what() << std::endl;
    }
  }
};

int main(int argc, char** argv)
{
  std::promise<int> div_promise;

  std::shared_future<int> div_result = div_promise.get_future();

  Div div;
  std::thread div_thread(div, std::move(div_promise), 20, 10);

  Requestor req;
  std::thread shared_thread1(req, div_result);
  std::thread shared_thread2(req, div_result);
  std::thread shared_thread3(req, div_result);
  std::thread shared_thread4(req, div_result);

  div_thread.join();

  shared_thread1.join();
  shared_thread2.join();
  shared_thread3.join();
  shared_thread4.join();

  return 0;
}
