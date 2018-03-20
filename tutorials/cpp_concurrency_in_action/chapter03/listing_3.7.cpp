///////////////////////////////////////////////////////////////////////////////
//
// Using a lock hierarchy to prevent deadlock
//
///////////////////////////////////////////////////////////////////////////////

#include <mutex>

class hierarchical_mutex
{
  explicit hierarchical_mutex(unsigned level)
  {}

  void lock()
  {}
  void unlock()
  {}
};

hierarchical_mutex high_level_mutex(10000);
hierarchical_mutex low_level_mutex(500);

int do_low_level_stuff()
{
  return 42;
}

int low_level_func()
{
  std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
  return do_low_level_stuff();
}

void high_level_stuff(int some_param)
{}

void high_level_func()
{
  std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
  high_level_stuff(low_level_func());
}

///////////////////////////////////////////////////////////////////////////////
//
// thread a abides by the rules.

void thread_a()
{
  high_level_func();
}

///////////////////////////////////////////////////////////////////////////////

hierarchical_mutex other_mutex(100);

void do_other_stuff()
{}

void other_stuff()
{
  high_level_func();
  do_other_stuff();
}

///////////////////////////////////////////////////////////////////////////////
//
// thread b disregards the rules and therefore will fail in runtime.

void thread_b()
{
  std::lock_guard<hierarchical_mutex> lk(other_mutex);
  other_stuff();
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  return 0;
}
