///////////////////////////////////////////////////////////////////////////////
//
// quick sort with recursion
// quick sort algorithm is unstable, influenced by given sequence.
//
// Following code give two implementations
// First, use the STL algorithm
// Second, implement by myself
//
// Time Complexity:
// average: O (n log n)
// worst:   O (n ^ 2)
//
// NOTE:
// 1) Take care the differece between c++11 and c++14 because of
// template deduction
//
// 2) the quick-sort does not support non-index based container,
// such as std::list, because list is implemented by linked list.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <random>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
//
// C++11 version

template <typename It>
using value_type_t = typename std::iterator_traits<It>::value_type;

template <class FwdIt, class Compare=std::less<value_type_t<FwdIt>>>
void quickSort(FwdIt first, FwdIt last, Compare cmp = Compare{})
{
  auto const N = std::distance(first, last);
  if (N <= 1) return;
  auto const pivot = std::next(first, N / 2);
  std::nth_element(first, pivot, last, cmp);
  quickSort(first, pivot, cmp);
  quickSort(pivot, last, cmp);
}

///////////////////////////////////////////////////////////////////////////////
//
// C++14 version

// template <class FwdIt, class Compare=std::less<>>
// void quickSort(FwdIt first, FwdIt last, Compare cmp=Compare{})
// {
//   auto const N = std::distance(first, last);
//   if (N <= 1) return;
//   auto const pivot = std::next(first, N / 2);
//   std::nth_element(first, pivot, last, cmp);
//   quickSort(first, pivot, cmp);
//   quickSort(pivot, last, cmp);
// }

///////////////////////////////////////////////////////////////////////////////
//
// Helper functions to generate data and print all data to std::cout

template <typename T>
void printAll(T start, T end, const std::string &title="")
{
  if (!title.empty())
    std::cout << title << " : ";

  for (auto i = start; i != end; ++i)
    std::cout << *i << ", ";
  std::cout << std::endl;
}

template <typename T, typename V>
void generateRand(T start, T end, V startValue)
{
  std::iota(start, end, startValue);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::shuffle(start, end, gen);
}

///////////////////////////////////////////////////////////////////////////////
//
// forward declaration
int partition(std::vector<int>&, int, int);

void quick_sort(std::vector<int>& array, int first, int last)
{
  int pivot;

  if (first < last)
  {
    pivot = partition(array, first, last);
    quick_sort(array, first, pivot);
    quick_sort(array, pivot+1, last);
  }
}

int partition(std::vector<int>& array, int first, int last)
{
  int p = first;
  int pivot_data = array[first];

  for (int i = first+1; i <= last; ++i)
  {
    if (array[i] <= pivot_data)
    {
      ++p;
      std::swap(array[i], array[p]);
//      std::iter_swap(array.begin() + i, array.begin() + p);
    }
  }
  std::swap(array[p], array[first]);
//  std::iter_swap(array.begin() + p, array.begin() + first);

  return p;
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////
  //
  // Test int array
  {
    int intArray[5];
    generateRand(intArray, intArray + 5, 10);
    quickSort(intArray, intArray + 5);
    printAll(intArray, intArray + 5, "int array");
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  // Test STL container
  {
    std::vector<int> arr = {8, 5, 2, 9, 10, 23};
    quickSort(arr.begin(), arr.end());
    printAll(arr.begin(), arr.end(), "STL container");
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  // Only one element
  {
    std::vector<int> arr1{1};
    quick_sort(arr1, 0, arr1.size()-1);
    printAll(arr1.begin(), arr1.end(), "only one element");
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  // Two elements
  {
    std::vector<int> arr1{1, 2};
    quick_sort(arr1, 0, arr1.size()-1);
    printAll(arr1.begin(), arr1.end(), "only two elements");
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  // Random sequence
  {
    std::vector<int> arr1{5, 7, 3, 4, 1, 9, 2 , 8, 10, 6};
    quick_sort(arr1, 0, arr1.size()-1);
    printAll(arr1.begin(), arr1.end(), "random sequence");
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  // Reverse sequence
  {
    std::vector<int> arr1{9, 8, 7, 6, 5, 4, 3, 2, 1};
    quick_sort(arr1, 0, arr1.size()-1);
    printAll(arr1.begin(), arr1.end(), "reverse sequence");
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  // Only one placed in wrong place
  {
    std::vector<int> arr1{1, 2, 3, 4, 5, 7, 6, 8, 9};
    quick_sort(arr1, 0, arr1.size()-1);
    printAll(arr1.begin(), arr1.end(), "only one wrong place");
  }

  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
