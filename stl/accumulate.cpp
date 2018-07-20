#include <iostream>
#include <vector>
#include <numeric>

int main(int argc, char* argv[])
{
  std::vector<int> vi{1, 2, 3, 4, 5, 6, 7};

  // these two are equivalent, the default behavior plus each element.
  auto sum = std::accumulate(begin(vi), end(vi), 0);
  auto sum1 = std::accumulate(begin(vi), end(vi), 0, std::plus<>{});

  std::cout << sum << " " << sum1 << std::endl;

  return 0;
}
