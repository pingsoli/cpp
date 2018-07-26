#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

int main(int argc, char *argv[])
{
  {
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {      3, 4, 5, 6, 7};
    std::vector<int> dst;

    // std::set_union(v1.begin(), v1.end(),
    //     v2.begin(), v2.end(),
    //     std::back_inserter(dst));

    // 3, 4, 5 are intersection
    // std::set_intersection(v1.begin(), v1.end(),
    //                       v2.begin(), v2.end(),
    //                       std::back_inserter(dst));

    for (const auto &i : dst)
      std::cout << i << ' ';
    std::cout << '\n';
  }

  return 0;
}
