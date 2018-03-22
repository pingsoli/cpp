///////////////////////////////////////////////////////////////////////////////
//
// Parallel Quicksort using futures
//
///////////////////////////////////////////////////////////////////////////////

#include <future>
#include <list>
#include <iostream>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////////
//
// If you recurse down 10 times, you'll have 2^10 (1024) threads running
// if the hardware concurrency.

template <typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
  if (input.empty())
    return input;
  std::list<T> result;
  result.splice(result.begin(), input, input.begin());
  const T& pivot = *result.begin();

  auto devide_point = std::partition(input.begin(), input.end(),
      [&](const T& t) { return t < pivot; });

  std::list<T> lower_part;
  lower_part.splice(lower_part.begin(), input, input.begin(), devide_point);

  std::future<std::list<T> > new_lower(
      std::async(&parallel_quick_sort<T>, std::move(lower_part)));

  auto new_higher(
      parallel_quick_sort(std::move(input)));

  result.splice(result.end(), new_higher);
  result.splice(result.begin(), new_lower.get());
  return result;
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
void traverse(const std::list<T>& input)
{
  std::for_each(input.cbegin(), input.cend(),
      [](const T& i) { std::cout << i << ' '; });
  std::cout << std::endl;
}

int main(int argc, char** argv)
{
  std::list<int> input = {5, 7, 3, 4, 1, 9, 2, 8, 10, 6};

  std::list<int> result(parallel_quick_sort(input));

  traverse(result);

  return 0;
}
