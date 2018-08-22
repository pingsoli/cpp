////////////////////////////////////////////////////////////////////////////////
// there are three classic algorithms using stl algorithm
// it's more concise approaches.
// 1) insertition sort
// 2) quick sort
// 3) trim string (trimRight, trimRight and trim operations)
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <string>
#include <locale>
#include <numeric>
#include <vector>
#include <random>

#ifndef __func__
  #define __func__ __FUNCTION__
#endif

#define PRINT_TEST_TITLE() std::cout << std::endl << "*** " \
                                     << __func__ << " ***" << std::endl
// Helper functions

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

// 1. insertionSort in just two lines of code
template <typename T>
void insertionSort(T start, T end)
{
  for (auto i = start; i != end; ++i)
    std::rotate(std::upper_bound(start, i, *i), i, std::next(i));
}

void insertionSortTest()
{
  PRINT_TEST_TITLE();

  int intArray[5];
  generateRand(intArray, intArray + 5, 1);
  printAll(intArray, intArray + 5, "before ");

  insertionSort(intArray, intArray + 5);
  printAll(intArray, intArray + 5, "after ");
}

// Take care, there are some difference between C++11 and C++14.
// Template deduction.
// C++ 11
// template <class It>
// using value_type_t = typename std::iterator_traits<It>::value_type;
//
// template <class FwdIt, class Compare=std::less<value_type_t<FwdIt>>>
// void quickSort(FwdIt first, FwdIt last, Compare cmp=Compare{})
// { ... }
//
// C++ 14
// template <class FwdIt, class Compare=std::less<>>
// void quickSort(FwdIt first, FwdIt last, Compare cmp=Compare{})
// { ... }

// 2. quick sort made with std::algorithm building blocks
template <class FwdIt, class Compare=std::less<>>
void quickSort(FwdIt first, FwdIt last, Compare cmp=Compare{})
{
  auto const N = std::distance(first, last);
  if (N <= 1) return;
  auto const pivot = std::next(first, N / 2);
  std::nth_element(first, pivot, last, cmp);
  quickSort(first, pivot, cmp);
  quickSort(pivot, last, cmp);
}

void quickSortTest()
{
  PRINT_TEST_TITLE();

  int intArray[5];
  generateRand(intArray, intArray + 5, 1);
  printAll(intArray, intArray + 5, "before ");

  quickSort(intArray, intArray + 5); 
  printAll(intArray, intArray + 5, "after ");
}

// 3. trim strings
std::string trimLeft(const std::string &s)
{
  auto temp = s;
  temp.erase(std::begin(temp), std::find_if(
        std::begin(temp), std::end(temp),
        [] (char c) { return !std::isspace(c, std::locale()); }));
  return temp;
}

#ifdef __GNUC__
std::string trimRight(const std::string &s)
{
  auto temp = s;
  const auto tempRbeg = temp.rbegin();
  const auto tempRend = temp.rend();
  temp.erase(std::find_if(tempRbeg, tempRend,
             [](char c) { return !std::isspace(c, std::locale()); }
       ).base(), std::end(temp));
  return temp;
}
#else
std::string trimRight(const std::string &s)
{
  auto temp = s;
  temp.erase(std::find_if(std::rbegin(temp), std::rend(temp), 
        [] (char c) { return !isspace(c, std::locale();)}
    ).base(), std::end(temp));
  return temp;
}
#endif

std::string trim(const std::string &s)
{
  return trimLeft(trimRight(s));
}

void trimStringTest()
{
  PRINT_TEST_TITLE();

  std::string test = "   hello world 1     ";
  std::cout << "|" << test << "| -> |"
                   << trimLeft(test) << "|" << std::endl; 

  std::string test1 = "     hello world 2    ";
  std::cout << "|" << test1 << "| -> |"
                   << trimRight(test1) << "|" << std::endl;

  std::string test2 = "     hello world 3     ";
  std::cout << "|" << test2 << "| -> |"
                   << trim(test2) << "|" << std::endl;
}

int main()
{
  // 1:
  insertionSortTest();

  // 2:
  quickSortTest();

  // 3:
  trimStringTest();

  return 0;
}
