///////////////////////////////////////////////////////////////////////////////
//
// Relaxed operations have very few ordering requirements
//
///////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <thread>
#include <iostream>

std::atomic<bool> x{false}, y{false};
std::atomic<int> z{0};

void write_x_then_y()
{
  x.store(true, std::memory_order_relaxed);
  y.store(true, std::memory_order_relaxed);
}

void read_x_then_y()
{
  while (!y.load(std::memory_order_relaxed));
  if (x.load(std::memory_order_relaxed))
    ++z;
}

int main(int argc, char** argv)
{
  std::thread a(write_x_then_y);
  std::thread b(read_x_then_y);

  a.join();
  b.join();

  // z maybe 0, because the load of x can read false,
  // even though the load of y reads true and the score of x happens-before
  // the store of y.
  std::cout << z << std::endl;
  return 0;
}
