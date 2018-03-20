///////////////////////////////////////////////////////////////////////////////
//
// A simple hierarchical mutex
//
///////////////////////////////////////////////////////////////////////////////

#include <mutex>
#include <stdexcept>
#include <climits> // ULONG_MAX
#include <thread>
#include <iostream>

class hierarchical_mutex
{
  std::mutex internal_mutex;
  unsigned long const hierarchy_value;
  unsigned long previous_hierarchy_value;
  static thread_local unsigned long this_thread_hierarchy_value;

  void check_for_hierarchy_violation()
  {
    if (this_thread_hierarchy_value <= hierarchy_value)
    {
      throw std::logic_error("mutex hierarchy violation");
    }
  }

  void update_hierarchy_value()
  {
    previous_hierarchy_value = this_thread_hierarchy_value;
    this_thread_hierarchy_value = hierarchy_value;
  }

public:
  explicit hierarchical_mutex(unsigned long value) :
    hierarchy_value(value),
    previous_hierarchy_value(0)
  {}

  void lock()
  {
    std::cout << "lock " << hierarchy_value << std::endl;

    check_for_hierarchy_violation();
    internal_mutex.lock();
    update_hierarchy_value();
  }

  void unlock()
  {
    std::cout << "unlock " << hierarchy_value << std::endl;

    this_thread_hierarchy_value = previous_hierarchy_value;
    internal_mutex.unlock();
  }

  bool try_lock()
  {
    std::cout << "try lock " << hierarchy_value << std::endl;

    check_for_hierarchy_violation();
    if (!internal_mutex.try_lock())
      return false;

    update_hierarchy_value();
    return true;
  }
};

thread_local unsigned long
hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX);

hierarchical_mutex m1(42);
hierarchical_mutex m2(2000);

///////////////////////////////////////////////////////////////////////////////
//
// use the same sequence to lock the mutex based on hierarchy.
// make sure to lock the bigger hierarchy lock first.

void func1()
{
  std::lock_guard<hierarchical_mutex> lk2(m2);
  std::lock_guard<hierarchical_mutex> lk1(m1);

  // do something
}

void func2()
{
  std::lock_guard<hierarchical_mutex> lk1(m2);
  std::lock_guard<hierarchical_mutex> lk2(m1);

  // do something
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  std::thread t1(func1);
  std::thread t2(func2);

  t1.join();
  t2.join();

  return 0;
}
