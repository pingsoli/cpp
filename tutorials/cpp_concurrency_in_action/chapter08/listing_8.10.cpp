///////////////////////////////////////////////////////////////////////////////
//
// An implementation of parallel find algotithm using std::async
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <atomic>
#include <future>
#include <iostream>

template <typename Iterator, typename MatchType>
Iterator parallel_find_impl(Iterator first, Iterator last,
                            MatchType match,
                            std::atomic<bool>& done)
{
  try
  {
    unsigned long const length = std::distance(first, last);
    unsigned long const min_per_thread = 25;

    if (length < (2*min_per_thread))
    {
      for (; (first != last) && !done.load(); ++first)
      {
        if (*first == match)
        {
          done = true;
          return first;
        }
      }
      return last;
    }
    else
    {
      Iterator const mid_point = first + (length / 2);

      std::future<Iterator> async_result =
        std::async(&parallel_find_impl<Iterator, MatchType>,
            mid_point, last, match, std::ref(done));

      Iterator const direct_result =
        parallel_find_impl(first, mid_point, match, done);

      return (direct_result == mid_point) ?
        async_result.get() : direct_result;
    }
  }
  catch (...)
  {
    done = true;
    throw;
  }
}

template <typename Iterator, typename MatchType>
Iterator parallel_find(Iterator first, Iterator last, MatchType match)
{
  std::atomic<bool> done{false};
  return parallel_find_impl(first, last, match, done);
}

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////
  //
  unsigned long const loop_count   = 1000000;
  unsigned long const search_value = 1000001;

  std::vector<int> vi;
  vi.reserve(loop_count);

  for (unsigned long i = 0; i < loop_count; ++i)
  {
    vi.push_back(i);
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  // STL std::find algorithm

  {
    auto it = std::find(vi.begin(), vi.end(), search_value);

    if (it != vi.end())
    {
      std::cout << "Found " << *it << '\n';
    }
    else
    {
      std::cout << "Not found" << std::endl;
    }
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  // parallel user-defined find

  {
    auto it = parallel_find(vi.begin(), vi.end(), search_value);

    if (it != vi.end())
    {
      std::cout << "Found " << *it << '\n';
    }
    else
    {
      std::cout << "Not found" << std::endl;
    }
  }

  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
