///////////////////////////////////////////////////////////////////////////////
//
// future, packaged_task, thread
//
// packaged_task is a package of tasks, will be moved to every thread
// we can get future from packaged_task through get_future method
//
// separate the job and result
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <future>
#include <chrono>
#include <thread>

int countdown(int from, int to)
{
  for (int i = from; i != to; --i)
  {
    std::cout << i << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << "Lift off\n";
  return from - to;
}

int main(int argc, char** argv)
{
  std::packaged_task<int(int, int)> task(countdown);
  std::future<int> ret = task.get_future();

  std::thread t1(std::move(task), 10, 0);

  int value = ret.get();

  std::cout << "The countdown lasted for " << value << " seconds.\n";

  t1.join();

  return 0;
}
