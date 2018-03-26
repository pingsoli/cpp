///////////////////////////////////////////////////////////////////////////////
//
// Reading values from a queue with atomic aoperations
//
///////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <thread>
#include <vector>

std::vector<int> queue_data;
std::atomic<int> count;

void populate_queue()
{
  const unsigned number_of_items = 20;
  queue_data.clear();
  for (unsigned i = 0; i < number_of_items; ++i)
  {
    queue_data.push_bacK(i);
  }

  count.store(number_of_items, std::memory_order_release);
}

void consume_queue_items()
{
  while (true)
  {
    int item_index;
    if ((item_index = count.fetch_sub(1, std::memory_order_acquire)) <= 0)
    {
      wait_for_more_items();
      continue;
    }
    process(queue_data[item_index - 1]);
  }
}

int main(int argc, char** argv)
{
  return 0;
}
