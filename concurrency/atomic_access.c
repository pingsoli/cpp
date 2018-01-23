#include "atomic_access.h"

#include <atomic>
#include <thread>
#include <assert.h>

std::atomic<bool> x, y;
std::atomic<int>  z;

/*
 * There is no way to promise the exectuting sequence of
 * operation 1 and operation 2. Maybe operation 1 is after 
 * operation 2. So, y may be ture, but x is false. 
 * It happened rarely, but isn't impossible.
 */
void write_x_then_y()
{
  x.store(true, std::memory_order_relaxed); // operation 1
  y.store(true, std::memory_order_relaxed); // operation 2
}

void read_y_then_x()
{
  while (!y.load(std::memory_order_relaxed)); // operation 3
  if (x.load(std::memory_order_relaxed))      // operation 4
    ++z;
}

/*
 * std::memory_order_relaxed is unorder, 
 * so, assert is maybe executed.
 */
void run_atomic_test()
{
  x = false;
  y = false;
  z = 0;

  std::thread a(write_x_then_y);
  std::thread b(read_y_then_x);
  
  a.join();
  b.join();

  assert(z.load() != 0);
}
