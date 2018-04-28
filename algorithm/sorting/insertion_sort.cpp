////////////////////////////////////////////////////////////////////////////////
//
// insertion sort
// compare current with before elements of the list
//
// Time complexity
// worst case:   O(n ^ 2)
// average case: O(n ^ 2)
// best case:    O(n)
//
////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <iostream>
#include <random>

void insertion_sort(std::vector<int> &array)
{
  std::size_t size = array.size();
  int k;

  for (int i = 1; i < size; ++i)
  {
    k = i;
    for (int j = k - 1; j >= 0; --j)
    {
      if (array[k] < array[j])
      {
        std::swap(array[j], array[k]);
        k = j;
      }
    }
  }
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
//  gen_random(a, 20);
//  gen_random(a, 0);
//  gen_random(a, 1);
//  gen_random(a, 2);

  print(a);

  insertion_sort(a);

  print(a);

  return 0;
}
