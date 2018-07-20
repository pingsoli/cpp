////////////////////////////////////////////////////////////////////////////////
// Keep in mind
// 1) Use std::reduce when you want your accumulation to run in parallel.
// 2) Ensure that the operation you want to use is both associate and commuative.
// 3) Remember that the default initial value is produced by default construction,
// and that this may not be correct for your operation.
////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <iostream>
#include <chrono>
#include <vector>
#include <execution>

int main(int argc, char* argv[])
{
  std::vector<double> v(10'000'007, 0.5);

  {
    auto t1 = std::chrono::high_resolution_clock::now();
    double result = std::accumulate(begin(v), end(v), 0.0);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = t2 - t1;
    std::cout << std::fixed << "std::accumulate result "
      << result << " took " << ms.count() << '\n';
  }

  {
    auto t1 = std::chrono::high_resolution_clock::now();
    double result = std::reduce(std::execution::par, v.begin(), v.end(), 0.0);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = t2 - t1;
    std::cout << "std::reduce result "
      << result << " took " << ms.count() << '\n';
  }

  return 0;
}
