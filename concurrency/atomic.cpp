///////////////////////////////////////////////////////////////////////////////
// memory model, memory order, non-atomic and atomic
//
// References
// [1] https://stackoverflow.com/questions/6319146/c11-introduced-a-standardized-memory-model-what-does-it-mean-and-how-is-it-g
// [2] https://bartoszmilewski.com/2008/12/01/c-atomics-and-memory-ordering/
///////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <thread>
#include <iostream>
#include <mutex>

///////////////////////////////////////////////////////////////////////////////
// Under c++11, the result is undefined behavior; because loads and stores need
// to be atomic in general.
//
// load - read from the variable(in memory)
// store - write a value to the variable(in memory)

int x{0}, y{0};      // global varible, but not atomic
std::mutex mu; // protect std::cout

// the order of execution ?
// maybe y = 37 is executed before x = 17.
// so, [0 37], [17 0], [0 0], [17 37] are both possible.
void thread_one() {
  x = 17;
  y = 37;
}

void thread_two() {
  std::lock_guard<std::mutex> lk(mu);
  std::cout << x << ' ' << y << std::endl;
}

void non_atomic_test() {
  for (int i = 0; i < 10; ++i) {
    std::thread t2(thread_two);
    std::thread t1(thread_one);

    t1.join();
    t2.join();

    x = 0;
    y = 0;
  }
}

///////////////////////////////////////////////////////////////////////////////
// atomic version, the result the one of: 0 0, 0 17, 37 17

std::atomic<int> ax{0}, ay{0};

void thread_one_atomic() {
  ax.store(17);
  ay.store(37);
}

void thread_two_atomic() {
  std::cout << ay.load() << " ";
  std::cout << ax.load() << std::endl;
}

void atomic_test() {
  std::thread t2(thread_two_atomic);
  std::thread t1(thread_one_atomic);

  t1.join();
  t2.join();
}

///////////////////////////////////////////////////////////////////////////////
// memory order, memory_order_relaxed tolerate all sequence
// it can tolerate 37 0 as output from this program
// 0 0, 0 17, 37 17, even 37 0, which is mean ay is assigned before ax.
//
// but the output 17 37 is a little wierd.

void thread_one_with_memory_order() {
  ax.store(17, std::memory_order_relaxed);
  ay.store(37, std::memory_order_relaxed);
}

void thread_two_with_memory_order() {
  std::cout << ay.load(std::memory_order_relaxed) << " ";
  std::cout << ax.load(std::memory_order_relaxed) << std::endl;
}

void atomic_with_memory_order_test() {
  std::thread t2(thread_two_with_memory_order);
  std::thread t1(thread_one_with_memory_order);

  t1.join();
  t2.join();
}

///////////////////////////////////////////////////////////////////////////////
// memory order, memory_order_release
// only allow: 0 0, 0 17, 37 17, no 37 0

void thread_one_with_memory_order_release() {
  ax.store(17, std::memory_order_release);
  ay.store(37, std::memory_order_release);
}

void thread_two_with_memory_order_release() {
  std::cout << ay.load(std::memory_order_acquire) << " ";
  std::cout << ax.load(std::memory_order_acquire) << std::endl;
}

void atomic_with_memory_order_release_test() {
  std::thread t1(thread_two_with_memory_order_release);
  std::thread t2(thread_one_with_memory_order_release);

  t1.join();
  t2.join();
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{

  // non_atomic_test();
  atomic_test();
  // atomic_with_memory_order_test();
  // atomic_with_memory_order_release_test();

  return 0;
}
