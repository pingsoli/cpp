#ifndef THREAD_BARRIER_H_
#define THREAD_BARRIER_H_

#include <cstddef>
#include <condition_variable>
#include <mutex>

#include <boost/assert.hpp>

class thread_barrier
{
private:
  std::size_t initial_;
  std::size_t current_;
  bool        cycle_{ true };

  std::mutex mtx_{};
  std::condition_variable cond{};

public:
  explicit thread_barrier(std::size_t initial) :
    initial_{initial},
    current_{initial_}
  {
      BOOST_ASSERT( 0 != initial );
  }

  thread_barrier(thread_barrier const&)            = delete;
  thread_barrier& operator=(thread_barrier const&) = delete;

  bool wait() {
    std::unique_lock<std::mutex> lk(mtx_);
    const bool cycle = cycle_;

    if (0 == --current_) {
      cycle_  = ! cycle_;
      current_ = initial_;

      lk.unlock();
      cond.notify_all();
      return true;
    } else {
      cond.wait(lk, [&](){ return cycle != cycle_; });
    }

    return false;
  }
};

#endif /* THREAD_BARRIER_H_ */
