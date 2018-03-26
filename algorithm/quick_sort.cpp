///////////////////////////////////////////////////////////////////////////////
//
// quick sort with recursion
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

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////

  int intArray[5];
  generateRand(intArray, intArray + 5, 10);
  printAll(intArray, intArray + 5, "before ");

  quickSort(intArray, intArray + 5);
  printAll(intArray, intArray + 5, "after ");

  ////////////////////////////////////////////////////////////////////////////

  std::vector<int> arr = {8, 5, 2, 9, 10, 23};

  printAll(arr.begin(), arr.end(), "before");
  quickSort(arr.begin(), arr.end());
  printAll(arr.begin(), arr.end(), "after");

  ////////////////////////////////////////////////////////////////////////////

  return 0;
}
