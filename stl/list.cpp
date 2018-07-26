#include <list>
#include <iostream>
#include <algorithm>

int main(int argc, char *argv[])
{
  std::list<int> li = {1, 2, 3, 4, 5, 2, 3, 4, 5, 6, 7, 8};

  // std::find basic usage
  std::list<int>::iterator it = std::find(li.begin(), li.end(), 2);
  if (it != li.end()) {
    std::cout << "Found " << *it << '\n';
  } else {
    std::cout << "Not Found!" << '\n';
  }

  // std::cout
  std::size_t count = std::count(li.begin(), li.end(), 2);
  std::cout << count << '\n';

  return 0;
}
