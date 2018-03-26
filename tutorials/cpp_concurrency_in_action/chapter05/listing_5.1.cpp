///////////////////////////////////////////////////////////////////////////////
//
// Implementation of a spinlock mutex using std::atomic_flag
//
///////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <chrono>
#include <thread>
#include <iostream>

class spinlock_mutex
{
  std::atomic_flag flag;
public:
  spinlock_mutex():
    flag(ATOMIC_FLAG_INIT)
  {}

  void lock()
  {
    while (flag.test_and_set(std::memory_order_acquire))
      std::cout << "waiting for unlock" << std::endl;
  }

  void unlock()
  {
    flag.clear(std::memory_order_release);
  }
};

// protect a
spinlock_mutex mu;

// global shared variable, is just a test
int a;

void thread_one()
{
  mu.lock();

  // sleep 1 seconds
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  ++a;
  mu.unlock();
}

void thread_two()
{
  mu.lock();
  --a;
  mu.unlock();
}

int main(int argc, char** argv)
{
  std::thread t1(thread_one);
  std::thread t2(thread_two);

  t1.join();
  t2.join();

  std::cout << "Final result: " << a << std::endl;

  return 0;
}
