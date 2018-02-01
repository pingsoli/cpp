/*
 * What is wrok-stealing ?
 * If the local ready-queue runs out of ready fibers, ready fibers are stolen
 * from other schedulers. The victim schedulers(from which a ready fiber is
 * stolen) is selected at random.
 */
#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <deque>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

#include <boost/assert.hpp>
#include <boost/fiber/all.hpp>

#include "thread_barrier.hpp"

static std::size_t                           fiber_count{ 0 };
static std::mutex                            mtx_count{ };
static boost::fibers::condition_variable_any cnd_count{};

typedef std::unique_lock<std::mutex> lock_type;

void whatevah(char me) {
  try
  {
    std::thread::id my_thread = std::this_thread::get_id();
    {
      std::ostringstream buffer;
      buffer << "fiber " << me << " started on thread " << my_thread << '\n';
      std::cout << buffer.str() << std::flush;
    }

    for (unsigned i = 0; i < 10; ++i) {
      boost::this_fiber::yield();
      std::thread::id new_thread = std::this_thread::get_id();
      if (new_thread != my_thread) {
        my_thread = new_thread;
        std::ostringstream buffer;
        buffer << "fiber " << me << " switched to thread "
               << my_thread << '\n';
        std::cout << buffer.str() << std::endl;
      }
    }
  }
  catch (...)
  {
    std::cerr << "unhandle error" << std::endl;
  }

  lock_type lk(mtx_count);
  if (0 == --fiber_count) { // decrement fiber counter for each completed fiber
    lk.unlock();
    cnd_count.notify_all();  // notify all fibers waiting on `cnd_count`
  }
}

void thread(thread_barrier * b)
{
  std::ostringstream buffer;
  buffer << "thread started " << std::this_thread::get_id() << std::endl;
  std::cout << buffer.str() << std::flush;

  boost::fibers::use_scheduling_algorithm<
                        boost::fibers::algo::work_stealing>(4);

  b->wait();
  lock_type lk(mtx_count);
  cnd_count.wait(lk, []() { return 0 == fiber_count; });

  BOOST_ASSERT( 0 == fiber_count );
}

int main(int argc, char** argv)
{
  std::cout << "main thread started "
            << std::this_thread::get_id() << std::endl;

  boost::fibers::use_scheduling_algorithm<
                        boost::fibers::algo::work_stealing>(4);

  for (char c : std::string("abcdefghijklmnopqrstuvwxyz")) {
    /*
     * Launch a number of worker fibers; each work fiber pick up a character
     * that is passed as parameter to fiber-function `whatevah`.
     * Each worker fiber get detached.
     */
    boost::fibers::fiber([c]() { whatevah(c); }).detach();
    ++fiber_count;
  }

  thread_barrier b(4);
  std::thread threads[] = {
    /* Launch a couple of threads that join the work sharing. */

    std::thread(thread, & b),
    std::thread(thread, & b),
    std::thread(thread, & b)
  };

  b.wait();
  {
    lock_type lk(mtx_count);
    cnd_count.wait(lk, []() { return 0 == fiber_count; });
  }

  BOOST_ASSERT( 0 == fiber_count );
  for (std::thread &t : threads)
    t.join();

  std::cout << "done." << std::endl;
  return 0;
}
