// Prefer make-function than new directly.
//
// but there are some drawbacks of make_xxx function:
// 1) cannot specify deleter
// 2) conflict with the object has std::initializer_list constructor

#include <memory>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
  // create 2 or 10 elements ?
  auto spv = std::make_shared<std::vector<int>>(10, 20);
  auto upv = std::make_unique<std::vector<int>>(10, 20);

  // both creat 10 elements
  std::copy(std::begin(*spv), std::end(*spv),
      std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';

  std::copy(std::begin(*upv), std::end(*upv),
      std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';

  // what happend if we want to use std::initializer_list.
  auto initializer = { 10, 20 };
  auto ispv = std::make_shared<std::vector<int>>(initializer);
  auto iupv = std::make_unique<std::vector<int>>(initializer);

  std::copy(std::begin(*ispv), std::end(*ispv),
      std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';

  std::copy(std::begin(*iupv), std::end(*iupv),
      std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';

  return 0;
}
