#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
  std::vector<int> arr = {5, 6, 7, 8, 9};
  std::vector<int> another_arr = {1, 2, 3, 4};

  // Bad pratice
  // for (auto it = arr.begin(); it != arr.end(); ++it)
  // {
  //   another_arr.push_back(*it);
  // }

  // Better way, more consice, just copy the array to another
  std::copy(arr.begin(), arr.end(), std::back_inserter(another_arr));

  for (auto e : another_arr) {
    std::cout << e << '\n';
  }

  return 0;
}
