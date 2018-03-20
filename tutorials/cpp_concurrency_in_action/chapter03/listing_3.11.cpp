///////////////////////////////////////////////////////////////////////////////
//
// Thread-safe lazy initialization using a mutex
// Double-Checking Locking problem
//
///////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <mutex>
#include <iostream>


struct some_resource
{
  void do_something()
  {}
};

std::shared_ptr<some_resource> resource_ptr;
std::mutex resource_mutex;

///////////////////////////////////////////////////////////////////////////////
//
// unnecessary serialization problematic

void foo()
{
  std::unique_lock<std::mutex> lock(resource_mutex);
  if (!resource_ptr)
  {
    resource_ptr.reset(new some_resource);
  }
  lock.unlock();
  resource_ptr->do_something();
}

///////////////////////////////////////////////////////////////////////////////
//
// Double-Checking Locking
// it's not thread-safe, exists nasty race condition.
//
// here is the reason
// the read outside the lock (1) isn't sychronized with the write done by
// another thread inside the lock (3). This therefore creates a reace condition
// that covers not just the pointer itself but also the object pointed to;
// even if a thread sees the pointer written by another thread, it might not
// see the newly created instance of some_reource, resulting in the call to
// do_something() (4) operating on incorrect values.

void undefined_behavior_with_double_checked_locking()
{
  if (!resource_ptr)                         // 1
  {
    std::lock_guard<std::mutex> lk(resource_mutex);
    if (!resource_ptr)                       // 2
    {
      resource_ptr.reset(new some_resource);  // 3
    }
  }
  resource_ptr->do_something();              // 4
}

///////////////////////////////////////////////////////////////////////////////
//
// std::once_flag and std::call_once could deal with the situation.

std::once_flag resource_flag;

void init_resource()
{
  resource_ptr.reset(new some_resource);
}

void new_foo()
{
  std::call_once(resource_flag, init_resource);
  resource_ptr->do_something();
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  try
  {
//    foo();
    new_foo();
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
