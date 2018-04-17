////////////////////////////////////////////////////////////////////////////////
//
// Shell Sort
//
// References
// [1] https://www.youtube.com/watch?v=ddeLSDsYVp8
//
////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void shell_sort(std::vector<int>& array)
{
  for (int gap = array.size()/2; gap > 0; gap /= 2)
    for (int i = gap; i < array.size(); ++i)
      for (int j = i - gap; j >= 0 && array[j] > array[j+gap]; j -= gap)
        std::swap(array[j], array[j+gap]);
}

void print(std::vector<int> a, const std::string& msg)
{
  std::cout << msg << std::endl;
  for (int i = 0; i < a.size(); ++i)
    std::cout << a[i] << ' ';
  std::cout << std::endl;
}

int main(int argc, char** argv)
{
  std::vector<int> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  print(a, "before soring ...");
  shell_sort(a);
  print(a, "after sorting ...");

  return 0;
}

