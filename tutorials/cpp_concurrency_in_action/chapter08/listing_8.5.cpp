///////////////////////////////////////////////////////////////////////////////
//
// An exception-safe parallel version of std::accumulate using std::async
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <future>
#include <iostream>

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
  unsigned long const length = std::distance(first, last);
  unsigned long const max_chunk_size = 25;

  if (length <= max_chunk_size)
  {
    return std::accumulate(first, last, init);
  }
  else
  {
    Iterator mid_point = first;
    std::advance(mid_point, length/2);
    std::future<T> first_half_result =
      std::async(parallel_accumulate<Iterator, T>, first, mid_point, init);

    T second_half_result = parallel_accumulate(mid_point, last, T());
    return first_half_result.get() + second_half_result;
  }
}

int main(int argc, char** argv)
{
  std::vector<int> vi;
  for (int i = 0; i < 1000; ++i)
  {
    vi.push_back(10);
  }

  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  int sum = parallel_accumulate(vi.begin(), vi.end(), 0);
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  std::cout << "time elapsed: "
    << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
    << std::endl;

  return 0;
}
