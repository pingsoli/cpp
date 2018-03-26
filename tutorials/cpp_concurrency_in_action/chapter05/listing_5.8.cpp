///////////////////////////////////////////////////////////////////////////////
//
// Acquire-release operations can impose ordering on relaxed operations
//
// step 1 executes before step 2, and step 3 is after step 2
// the synchronous step: step 1 -> step 2 -> step 3 -> step 4
//
// z's value is 1 all the time.
//
///////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <thread>
#include <iostream>

std::atomic<bool> x{false}, y{false};
std::atomic<int> z{0};

void write_x_then_y()
{
  x.store(true, std::memory_order_relaxed);  // 1
  y.store(true, std::memory_order_release);  // 2
}

void read_y_then_x()
{
  while (!y.load(std::memory_order_acquire));  // 3
  if (x.load(std::memory_order_relaxed))       // 4
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
