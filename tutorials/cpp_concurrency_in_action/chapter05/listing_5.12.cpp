///////////////////////////////////////////////////////////////////////////////
//
// Relaxed operations can be ordered with fences
//
// atomic_thread_fence can keep the order of relaxed operations.
//
// the release fence 2 sychronizes-with the acquire fence 5, because the load
// from y are 4 reads the value stored at 3. This means that the store to x
// at 1 happens-before the load from x at 6, so the value read must be true.
//
///////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <thread>
#include <iostream>

std::atomic<bool> x{false}, y{false};
std::atomic<int> z{0};

void write_x_then_y()
{
  x.store(true, std::memory_order_relaxed); // 1
  std::atomic_thread_fence(std::memory_order_release); // 2
  y.store(true, std::memory_order_release);  // 3
}

void read_y_then_x()
{
  while (!y.load(std::memory_order_relaxed));  // 4
  std::atomic_thread_fence(std::memory_order_acquire);  // 5
  if (x.load(std::memory_order_relaxed))  // 6
    ++z;
}

int main(int argc, char** argv)
{
  std::thread a(write_x_then_y);
  std::thread b(read_y_then_x);

  a.join();
  b.join();

  std::cout << z << std::endl; // z will never be 0

  return 0;
}
