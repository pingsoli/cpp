///////////////////////////////////////////////////////////////////////////////
//
// Using std::lock() and std::unique_lock() in swap operation
//
///////////////////////////////////////////////////////////////////////////////

#include <mutex>

class some_big_object
{};

void swap(some_big_object& lhs, some_big_object& rhs)
{}

class X
{
private:
  some_big_object some_detail;
  mutable std::mutex m;

public:
  X(some_big_object const& sd)
    : some_detail(sd)
  {}

  friend void swap(X& lhs, X& rhs)
  {
    if (&lhs == &hs)
      return;

    // std::unique_lock and std::defer_lock
    // std::lock_guard and std::adopt_lock
    // they are essentially equivalent, you can review the listing_3.6.cpp file
    //
    std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);
    std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);
    std::lock(lock_a, lock_b);
    swap(lhs.some_detail, rh.some_detail);
  }
};

int main(int argc, char** argv)
{
  return 0;
}
