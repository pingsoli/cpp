#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char *argv[])
{
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::fill_n(std::back_inserter(v), 3, -1);
  for (int n : v)
    std::cout << n << ' ';

  return 0;
}
