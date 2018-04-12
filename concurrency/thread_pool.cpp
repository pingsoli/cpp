#include <iostream>
#include <mutex>
#include <thread>

#include "thread_pool.hpp"

std::mutex cout_mutex;

void worker(unsigned int thread_id)
{
  std::lock_guard<std::mutex> lk(cout_mutex);
  std::cout << "this thread id " << thread_id << std::endl;
}

int main(int argc, char** argv)
{
  ThreadPool thread_pool(4);

  for (unsigned i = 0; i < 10; ++i)
    thread_pool.enqueue(worker, i);

  return 0;
}
