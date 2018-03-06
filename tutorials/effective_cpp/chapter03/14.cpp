///////////////////////////////////////////////////////////////////////////////
//
// Item 14: Think carefully about copying behavior in resource-managing classes
//
// 1) Copying an RAII object entails copying the resource it manages, so the
// copying behavior of the resource determines the copying behavior of the
// RAII object.
//
// 2) Common RAII class copying behaviors are disallowing copying and
// performing reference counting. but other behaviors are possible.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>

class Mutex
{
};

class Lock
{
public:
  explicit Lock(Mutex* pm)
    : mutex_{pm}
  {
    lock(mutex_);
  }

  ~Lock() { unlock(mutex_); }

  void lock(Mutex* pm)
  {
    std::cout << "lock the mutex" << std::endl;
  }

  void unlock(Mutex* pm)
  {
    std::cout << "unlock the mutex" << std::endl;
  }

private:
  Mutex* mutex_;
};

int main(int argc, char** argv)
{

  Mutex mutex;

  // build a block to lock the critical area
  {
    Lock m1(&mutex);
  }

  return 0;
}
