////////////////////////////////////////////////////////////////////////////////
// create two threads, one of them occupy the std::mutex and another want to get
// the mutex, see what happens ?
// the other thread will wait for the mutex unlocked.
////////////////////////////////////////////////////////////////////////////////

#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>

std::mutex mux; // protect nothing.

void func1() {
  {
    std::unique_lock<std::mutex> locker{mux};

    // stimulate the real job.
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
  std::cout << "func1 finished after 2 seconds." << std::endl;
}

void func2() {
  std::lock_guard<std::mutex> locker{mux};
  std::cout << "hi, here is func2, I got the mutex after func1." << std::endl;
}

int main(int argc, char *argv[])
{
  std::thread t1(func1);
  std::thread t2(func2);

  // we suppose t1 runs before t2.

  t1.join();
  t2.join();

  return 0;
}
