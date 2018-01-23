#pragma once

/*
 * Test for std::async and std::future
 * I don't care about the processing of my data,
 * I just want to get the data in the end.
 * Maybe It will spend much time, but I don't care.
 *
 * std::async default behavior won't create a new thread.
 * We must specify std::launch::async on the std::async.
 */
#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <mutex>

/* Protect std::cout */
std::mutex cout_mutex;

int do_async_job()
{
  /* do nothing, just sleep and return */
  std::lock_guard<std::mutex> lk(cout_mutex);
  std::cout << "async thread id: " << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(2));
  return 100;
}

void do_other_thing()
{
  std::this_thread::sleep_for(std::chrono::seconds(2));
}

void main_job()
{
  auto start = std::chrono::high_resolution_clock::now();
 
  /* 
   * Don't add std::launch::async, async job will run on the same thread, or
   * async will create a new thread and run on the background.
   *
   * future.get() will make main thread wait for the async thread.
   */
  std::future<int> the_answer = std::async(std::launch::async, do_async_job);
  do_other_thing();

  std::lock_guard<std::mutex> lk(cout_mutex);
  std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
  std::cout << "the last answer is: " << the_answer.get() << std::endl;

  /* 
   * Async thread sleep 2s, main thread sleep 2s, but the answer it not 4s. 
   * It's 2s, but is not precise.
   */
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end - start;
  std::cout << "programming executing: " << elapsed.count() << " ms" << std::endl;
}
