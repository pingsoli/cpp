#pragma once

/*
 * Make container become devided block, and using multi-thread
 * to calculate the block of container separately.
 * Finaly, accumulate all block and get the last result.
 *
 * NOTE: std::thread may throw exception, we don't address it.
 */

#include <vector>
#include <thread>
#include <iterator>
#include <numeric>    /* std::accumulate */
#include <algorithm>

template <typename Iterator, typename T>
struct accumulate_block
{
  void operator()(Iterator first, Iterator last, T& result)
  {
    result = std::accumulate(first, last, result);
  }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
  /* Compute the number of all elements, if 0, return directly */
  unsigned long const length = std::distance(first, last);

  if (!length)
    return init;

  unsigned long const min_per_thread = 25;
  unsigned long const max_threads = 
    (length + min_per_thread - 1) / min_per_thread;

  /*
   * Use standard library to get CPU cores.
   * It maybe return 0, we must check it.
   */
  unsigned long const hardware_threads = 
    std::thread::hardware_concurrency();

  /*
   * Calculate the number of threads, 
   * I don't know whether it is best.
   */
  unsigned long const num_threads = 
    std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

  /*
   * Every thread is responsible for the block of iterator distance,
   * calculating the block and get the result. In the end, add all to 
   * last result.
   */
  unsigned long const block_size = length / num_threads;

  std::vector<T> results(num_threads);
  /* Include main thread, so we minus 1 */ 
  std::vector<std::thread> threads(num_threads - 1);

  Iterator block_start = first;
  for (unsigned long i = 0; i < (num_threads - 1); ++i)
  {
    Iterator block_end = block_start;
    
    std::advance(block_end, block_size);
    threads[i] = std::thread(
        accumulate_block<Iterator, T>(), 
        block_start, block_end, std::ref(results[i]));
    block_start = block_end;
  }

  accumulate_block<Iterator, T>()(
      block_start, last, results[num_threads - 1]);
  std::for_each(threads.begin(), threads.end(), 
      std::mem_fn(&std::thread::join));

  return std::accumulate(results.begin(), results.end(), init);
}
