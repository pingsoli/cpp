///////////////////////////////////////////////////////////////////////////////
//
// A parallel version of std::accumulate using std::packaged_task
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <functional>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

template <typename Iterator, typename T>
struct accumulate_block
{
  T operator()(Iterator first, Iterator last)
  {
    return std::accumulate(first, last, T());
  }
};

// template <typename Iterator, typename T>
// T accumulate_block(Iterator first, Iterator last)
// {
//   return std::accumulate(first, last, T());
// }

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
  unsigned long long length = std::distance(first, last);

  if (!length)
    return init;

  unsigned long const min_per_thread = 25;
  unsigned long const max_threads =
    (length + min_per_thread - 1)/min_per_thread;

  unsigned long const hardware_threads =
    std::thread::hardware_concurrency();

  unsigned long const num_threads =
    std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

  unsigned long const block_size = length / num_threads;

  std::cout << "max_threads: " << max_threads << std::endl;
  std::cout << "hardware_concurrency: " << hardware_threads << std::endl;
  std::cout << "num_threads: " << num_threads << std::endl;
  std::cout << "block_size: " << block_size << std::endl;

  std::vector<std::future<T>> futures(num_threads - 1);
  std::vector<std::thread> threads(num_threads - 1);

  Iterator block_start = first;
  for (unsigned long i = 0; i < (num_threads - 1); ++i)
  {
    Iterator block_end = block_start;
    std::advance(block_end, block_size);
    std::packaged_task<T(Iterator, Iterator)> task(
        std::move(accumulate_block<Iterator, T>()));
    futures[i] = task.get_future();
    threads[i] = std::thread(std::move(task), block_start, block_end);
    block_start = block_end;
  }

  T last_result = accumulate_block<Iterator, T>()(block_start, last);

  std::for_each(threads.begin(), threads.end(),
      std::mem_fn(&std::thread::join));

  T result = init;
  for (unsigned long i = 0; i < (num_threads - 1); ++i)
  {
    result += futures[i].get();
  }

  result += last_result;
  return result;
}

int main(int argc, char** argv)
{
  std::vector<int> vi;
  for (int i = 0; i < 50; ++i)
  {
    vi.push_back(10);
  }

  int sum = parallel_accumulate(vi.begin(), vi.end(), 0);
  std::cout << "sum = " << sum << std::endl;

  return 0;
}
