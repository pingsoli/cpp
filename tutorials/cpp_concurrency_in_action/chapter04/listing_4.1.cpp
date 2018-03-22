///////////////////////////////////////////////////////////////////////////////
//
// Waiting for data to process with a std::condition_variable
//
///////////////////////////////////////////////////////////////////////////////

#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <iostream>

// not thread-safe, only use in single thread
int count = 0;

bool more_data_to_process()
{
  return (count++ < 10);
}

struct data_chunk
{};

data_chunk prepare_data()
{
  return data_chunk();
}

void process(data_chunk&)
{}

bool is_last_chunk(data_chunk&)
{
  return true;
}

std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

void data_preparation_thread()
{
  while (more_data_to_process())
  {
    const data_chunk data = prepare_data();
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(data);

    std::cout << "prepare data finished" << std::endl;
    data_cond.notify_one();
  }
}

void data_processing_thread()
{
  while (true)
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, []{ return !data_queue.empty(); });
    data_chunk data = data_queue.front();
    data_queue.pop();
    lk.unlock();

    process(data);
    if (is_last_chunk(data))
      break;
  }
}

int main(int argc, char** argv)
{
  std::thread t1(data_preparation_thread);
  std::thread t2(data_processing_thread);

  t1.join();
  t2.join();

  return 0;
}
