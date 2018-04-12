///////////////////////////////////////////////////////////////////////////////
//
// A thread pool with waitble tasks
//
///////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "join_threads.hpp"
#include "threadsafe_queue.hpp"

#ifndef DEBUG
#define DEBUG 1
#endif

class function_wrapper
{
  struct impl_base
  {
    virtual void call() = 0;
    virtual ~impl_base() {}
  };

  std::unique_ptr<impl_base> impl;

  template <typename F>
  struct impl_type : impl_base
  {
    F f;
    impl_type(F&& f_): f(std::move(f_)) {}
    void call() { f(); }
  };

public:
  template <typename F>
  function_wrapper(F&& f) :
    impl{new impl_type<F>(std::move(f))}
  {}

  void operator()() { impl->call(); }

  function_wrapper() = default;

  function_wrapper(function_wrapper&& other) :
    impl(std::move(other.impl))
  {}

  function_wrapper& operator=(function_wrapper&& other)
  {
    impl = std::move(other.impl);
    return *this;
  }

  function_wrapper(const function_wrapper&)            = delete;
  function_wrapper(function_wrapper&)                  = delete;
  function_wrapper& operator=(const function_wrapper&) = delete;
};


class thread_pool
{
  std::atomic_bool                   done;
  threadsafe_queue<function_wrapper> work_queue;
  std::vector<std::thread>           threads;
  join_threads                       joiner;
  std::mutex                         cout_mutex;

  void worker_thread()
  {
    while (!done)
    {
      function_wrapper task;
      if (work_queue.try_pop(task))
      {
#if DEBUG
        std::lock_guard<std::mutex> lk(cout_mutex);
        std::cout << "runing task...\n";
#endif
        task();
      }
      else
      {
        std::this_thread::yield();

#if DEBUG
        std::lock_guard<std::mutex> lk(cout_mutex);
        std::cout << "thread "
          << std::this_thread::get_id() << " is waiting....\n";
#endif
      }
    }
  }

public:
  thread_pool() :
    done{false}, joiner{threads}
  {
    unsigned const thread_count = std::thread::hardware_concurrency();

    try
    {
      for (unsigned i = 0; i < thread_count; ++i)
      {
        threads.push_back(
            std::thread(&thread_pool::worker_thread, this));
      }
    }
    catch (...)
    {
      done = true;
      throw;
    }
  }

  ~thread_pool()
  {
    done = true;
  }

  unsigned capacity() const
  {
    return std::thread::hardware_concurrency();
  }

  template <typename FunctionType>
  std::future<typename std::result_of<FunctionType()>::type>
    submit(FunctionType f)
  {
    typedef typename std::result_of<FunctionType()>::type result_type;

    std::packaged_task<result_type()> task(std::move(f));
    std::future<result_type> res(task.get_future());
    work_queue.push(std::move(task));
    return res;
  }
};

///////////////////////////////////////////////////////////////////////////////

std::atomic<int> task_count{0};

// real task
int foo()
{
  return ++task_count;
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  std::vector<int> results;

  {
    std::vector<std::future<int>> futures;

    thread_pool pool;
    for (int i = 0; i < pool.capacity(); ++i)
      futures.push_back(pool.submit(foo));

    // push more tasks
    futures.push_back(pool.submit(foo));

    for(auto& item : futures)
      results.push_back(item.get());
  }

  for (auto& e : results)
    std::cout << e << ' ';
  std::cout << std::endl;

  return 0;
}
