////////////////////////////////////////////////////////////////////////////////
//
// Shell Sort
// Shell sort is unstable, depends on the gap.
//
// Description
// 7 6 8 9 3 2 10 5 1
// |-------|
//   |-------|
//     |-------|
//       |--------|
//         |--------|
// |-------|
// 1 2 8 5 3 6 10 9 7
// |---|
//   |---|
//     |---|
// |---|
//       |---|
//   |---|
//         |----|
//           |----|
// ...
// enable debug for more details.
//
// Time Complexity
// average: O (n ^ 5/4 ~ n ^ 3/2)
// worst:   O (n ^ 2)
//
// References
// [1] https://www.youtube.com/watch?v=ddeLSDsYVp8
//
////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define PINGSOLI_DEBUG 0

#if PINGSOLI_DEBUG

void shell_sort(std::vector<int>& array)
{
  for (int gap = array.size()/2; gap > 0; gap /= 2)
    for (int i = gap; i < array.size(); ++i)
      for (int j = i - gap; j >= 0; j -= gap)
      {
        for (int i = 0; i < array.size(); ++i)
          std::cout << array[i] << ' ';
        std::cout << std::endl;

        std::cout << array[j] << ' ' << array[j+gap] << std::endl;

        if (array[j] > array[j+gap])
          std::swap(array[j], array[j+gap]);
      }
}

#else

void shell_sort(std::vector<int>& array)
{
  for (int gap = array.size()/2; gap > 0; gap /= 2)
    for (int i = gap; i < array.size(); ++i)
      for (int j = i - gap; j >= 0 && array[j] > array[j+gap]; j -= gap)
        std::swap(array[j], array[j+gap]);
}

#endif

void print(std::vector<int> a, const std::string& msg)
{
  std::cout << msg << std::endl;
  for (int i = 0; i < a.size(); ++i)
    std::cout << a[i] << ' ';
  std::cout << std::endl;
}

int main(int argc, char** argv)
{
  std::vector<int> a{7, 6, 8, 9, 3, 2, 10, 5, 1};

  print(a, "before soring ...");
  shell_sort(a);
  print(a, "after sorting ...");

  return 0;
}
