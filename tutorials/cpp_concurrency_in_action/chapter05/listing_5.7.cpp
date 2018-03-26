///////////////////////////////////////////////////////////////////////////////
//
// Acquire-release doesn't imply a total ordering
//
///////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <thread>
#include <iostream>

std::atomic<bool> x{false}, y{false};
std::atomic<int>  z{0};

void write_x()
{
  x.store(true, std::memory_order_release);
}

void write_y()
{
  y.store(true, std::memory_order_release);
}

void read_x_then_y()
{
  while (!x.load(std::memory_order_acquire));
  if (y.load(std::memory_order_acquire))
    ++z;
}

void read_y_then_x()
{
  while (!y.load(std::memory_order_acquire));
  if (x.load(std::memory_order_acquire))
    ++z;
}

int main(int argc, char** argv)
{
  std::thread a(write_x);
  std::thread b(write_y);
  std::thread c(read_x_then_y);
  std::thread d(read_y_then_x);

  a.join();
  b.join();
  c.join();
  d.join();

  std::cout << z << std::endl;
  return 0;
}
