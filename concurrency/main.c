#include "accumulate_compute.h"
#include <iostream>
#include "future_thing.h"
#include "atomic_access.h"

void test_parallel_calculate();

int main(int argc, char *argv[])
{
//  test_parallel_calculate();
//  main_job();

  run_atomic_test(); 

  return 0;
}

void test_parallel_calculate()
{
  std::vector<int> arr = { 90, 12, 3, 89, 23, 5, 12, 
      89, 2390, 12, 334, 12, 90, 34, 10 };

  unsigned long r1 = std::accumulate(arr.begin(), arr.end(), 0);
  unsigned long r2 = parallel_accumulate(arr.begin(), arr.end(), 0);

  std::cout << "result: \n"
    << "blocking caculate: " << r1 << "\n"
    << "parallel caculate: " << r2 << std::endl;
}
