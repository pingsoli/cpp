////////////////////////////////////////////////////////////////////////////////
// there are three ways to create future.
// 1) std::packaged_task
// 2) std::promise
// 3) std::async
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <future>
#include <thread>

int main(int argc, char *argv[])
{
  // future from a packaged_task
  std::packaged_task<int()> task([] { return 7; });
  std::future<int> f1 = task.get_future();
  std::thread t(std::move(task));

  // future from an async()
  std::future<int> f2 = std::async(std::launch::async, [] { return 8; });

  // future from a promise
  std::promise<int> p;
  std::future<int> f3 = p.get_future();
  std::thread([&p] { p.set_value_at_thread_exit(9); }).detach();

  std::cout << "Waiting...." << '\n';

  f1.wait();
  f2.wait();
  f3.wait();

  std::cout << "Done!\nResults are: "
    << f1.get() << ' ' << f2.get() << ' ' << f3.get() << std::endl;

  t.join();

  return 0;
}
