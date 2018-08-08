////////////////////////////////////////////////////////////////////////////////
// NOTE: if the value is not well defined or not computable, return 0.
// so we must make sure the correct answer.
// if we want cross-platform.
//
// std::thread::hardware_concurrency is portable since C++11.
// so before C++ 11, there is no portable way.
////////////////////////////////////////////////////////////////////////////////
#include <thread>
#include <iostream>

int main(int argc, char *argv[])
{
  unsigned currentThreadsSupported = std::thread::hardware_concurrency();
  std::cout << currentThreadsSupported << '\n'; // 4
  // I check the result in UserBenchMarck.
  // My CPU is core i5-4210U which is 2 cores, 4 threads.

  return 0;
}
