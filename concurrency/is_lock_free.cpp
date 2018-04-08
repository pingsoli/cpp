///////////////////////////////////////////////////////////////////////////////
//
// Judge a type whether is lock-free
//
// NOTE
// -latomic library required when linking
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <atomic>
#include <utility>

struct A { int a[100]; };
struct B { int x, y; };

int main(int argc, char** argv)
{
  std::atomic<A> a;
  std::atomic<B> b;

  std::cout << std::boolalpha
    << "std::atomic<A> is lock free ? "
    << std::atomic_is_lock_free(&a) << '\n'
    << "std::atomic<B> is lock free ? "
    << std::atomic_is_lock_free(&b) << '\n';

  return 0;
}
