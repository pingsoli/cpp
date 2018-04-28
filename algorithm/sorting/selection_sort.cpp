////////////////////////////////////////////////////////////////////////////////
//
// selection sort
//
// find the smallest element every traversal of the list
//
// Time complexity
// worst case:   O (n ^ 2)
// best case:    O (n ^ 2)
// average case: O (n ^ 2)
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <random>
#include <vector>

void selection_sort(std::vector<int> &array)
{
  int size = array.size();

  for (int i = 0; i < size; ++i)
    for (int j = i + 1; j < size; ++j)
      if (array[i] > array[j])
        std::swap(array[i], array[j]);
}

void gen_random(
    std::vector<int> &array, int num, int start = 0, int end = 100)
{
  std::uniform_int_distribution<int> int_dist(start, end);
  std::random_device rd;   // Used to botain a seed from the random number engine
  std::mt19937 gen(rd());  // generator

  for (int i = 0; i < num; ++i)
    array.push_back(int_dist(gen));
}

void print(std::vector<int> &a) {
  for (int i = 0; i < a.size(); ++i)
    std::cout << a[i] << ' ';
  std::cout << std::endl;
}

int main(int argc, char** argv)
{
  std::vector<int> a;
  gen_random(a, 20);

  print(a);

  selection_sort(a);

  print(a);

  return 0;
}
