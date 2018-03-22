///////////////////////////////////////////////////////////////////////////////
//
// A sequential implementation of Quicksort
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <list>
#include <iostream>

template <typename T>
std::list<T> sequential_quick_sort(std::list<T> input)
{
  if (input.empty())
    return input;

  std::list<T> result;
  result.splice(result.begin(), input, input.begin());
  const T& pivot = *result.begin();

  auto devide_point = std::partition(input.begin(), input.end(),
      [&](const T& t) { return t < pivot; });

  std::list<T> lower_part;
  lower_part.splice(lower_part.end(), input, input.begin(), devide_point);

  auto new_lower(
      sequential_quick_sort(std::move(lower_part)));

  auto new_higher(
      sequential_quick_sort(std::move(input)));

  result.splice(result.end(), new_higher);
  result.splice(result.begin(), new_lower);

  return result;
}

template <typename T>
void traverse(const std::list<T>& c)
{
  std::for_each(c.cbegin(), c.cend(),
      [](const T& i){ std::cout << i << ' '; });
  std::cout << std::endl;
}

int main(int argc, char** argv)
{
  std::list<int> l = {5, 7, 3, 4, 1, 9, 2, 8 ,10, 6};

  /////////////////////////////////////////////////////////////////////////////
  //
  // std::move will destory the part of the list, we can make use of the
  // move semantics.

//  auto devide_point = l.begin();
//  std::advance(devide_point, 5);
//
//  std::list<int> lower_part;
//  lower_part.splice(lower_part.begin(), l, l.begin(), devide_point);
//
//  std::list<int> new_lower(std::move(lower_part));
//
//  traverse(new_lower);
//  traverse(l);

  /////////////////////////////////////////////////////////////////////////////

  std::list<int> result = sequential_quick_sort(l);
  traverse(result);

  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
