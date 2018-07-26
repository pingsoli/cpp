#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <numeric>

class ThreadPool
{
public:
  using Task = std::function<void()>;

  explicit ThreadPool(std::size_t numThreads) {
    start(numThreads);
  }

  ~ThreadPool() {
    stop();
  }

  ThreadPool(const ThreadPool&) = delete;
  ThreadPool(ThreadPool&&)      = delete;

  // basic enqueue, no return value.
  // void enqueue(Task task)
  // {
  //   {
  //     std::unique_lock<std::mutex> lk(tasks_mutex);
  //     tasks.emplace(std::move(task));
  //   }
  //   event_var.notify_one();
  // }

  // advanced enqueue with return value using future
  // template <typename T>
  // auto enqueue(T task) -> std::future<decltype(task())>
  // {
  //   auto wrapper = std::make_shared<
  //     std::packaged_task<decltype(task()) ()>>(std::move(task));
  //
  //   {
  //     std::unique_lock<std::mutex> lk(tasks_mutex);
  //     tasks.emplace([=] {
  //       (*wrapper)();
  //     });
  //   }
  //
  //   event_var.notify_one();
  //   return wrapper->get_future();
  // }

  template <typename Func, typename ...Args>
  auto enqueue(Func&& func, Args&&... args) ->
    std::future<typename std::result_of<Func(Args...)>::type>
  {
    using ret_type = typename std::result_of<Func(Args...)>::type;
    auto task = std::make_shared<std::packaged_task<ret_type()>>(
          std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
        );

    {
      std::unique_lock<std::mutex> lk(tasks_mutex);
      tasks.emplace([=] {
          (*task)(); // execute task
      });
    }

    event_var.notify_one();
    return task->get_future();
  }

private:
  void start(std::size_t numThreads)
  {
    for (auto i = 0u; i < numThreads; ++i)
    {
      threads.emplace_back([=] {
        while (true)
        {
          Task task;
          {
            std::unique_lock<std::mutex> lk(tasks_mutex);
            event_var.wait(lk, [=]{ return is_stopping || !tasks.empty(); });

            if (is_stopping && tasks.empty())
              break;

            // get one task from task queue
            task = std::move(tasks.front());
            tasks.pop();
          }
          task();
        }
      });
    }
  }

  void stop() noexcept
  {
    {
      std::unique_lock<std::mutex> lk(tasks_mutex);
      is_stopping = true;
    }

    event_var.notify_all();
    for (auto &thread : threads)
      thread.join();
  }

  std::vector<std::thread> threads;

  std::queue<Task> tasks;
  std::condition_variable event_var;
  std::mutex tasks_mutex;

  bool is_stopping = false;
};

int worker(int& i) {
  i = 100;
  return i;
}

int main(int argc, char *argv[])
{
  std::vector<std::future<int>> futures;
  std::size_t num_threads = 5;
  std::mutex cout_mutex;
  int total = 0;
  int param1 = 10;
  int param2 = 20;

  {
    ThreadPool pool{num_threads};
    futures.reserve(num_threads);

    for (int i = 0; i < num_threads - 2; ++i)
      futures.push_back(pool.enqueue([&, i] { // move semantics
          std::unique_lock<std::mutex> lk(cout_mutex);
          std::cout << i << '\t';
          return i;
      }));

    futures.push_back(pool.enqueue(worker, std::ref(param1)));
    futures.push_back(pool.enqueue([&] {
      param2 = 200;
      return param2;
    }));
  }

  std::cout << '\n';

  std::cout << "param1: " << param1 << '\n';
  std::cout << "param2: " << param2 << '\n';
  total = std::accumulate(futures.begin(), futures.end(), 0,
      [] (int x, std::future<int>& fut) { return x + fut.get(); });

  std::cout << "total num: " << total << std::endl;

  return 0;
}
