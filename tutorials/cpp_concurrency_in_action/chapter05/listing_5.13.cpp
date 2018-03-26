///////////////////////////////////////////////////////////////////////////////
//
// Enforcing ordering no nonatomic operations
//
// you saw the ordering effects back in listing-5.10 with memory_order_release/
// memory_order_consume pair ordering nonatomic accessses to a dynamically
// allocated object.
//
///////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <thread>
#include <iostream>

bool x = false;
std::atomic<bool> y{false};
std::atomic<int> z{0};

void write_x_then_y()
{
  x = true;
  std::atomic_thread_fence(std::memory_order_release);
  y.store(true, std::memory_order_relaxed);
}

void read_y_then_x()
{
  while (!y.load(std::memory_order_relaxed));
  std::atomic_thread_fence(std::memory_order_acquire);
  if (x)
    ++z;
}

int main(int argc, char** argv)
{
  std::thread a(write_x_then_y);
  std::thread b(read_y_then_x);

  a.join();
  b.join();

  std::cout << z << std::endl;
  return 0;
}
