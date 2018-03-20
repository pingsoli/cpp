///////////////////////////////////////////////////////////////////////////////
//
// Using std::lock() and std::lock_guard in a swap function
//
///////////////////////////////////////////////////////////////////////////////

#include <mutex>

class some_big_object
{};

void swap(some_big_object& lhs, some_big_object& rhs)
{
}

class X
{
private:
  some_big_object some_detail;
  mutable std::mutex m;

public:
  X(some_big_object const& sd) : some_detail(sd) {}

  friend void swap(X& lhs, X& rhs)
  {
    if (&lhs == &rhs)
      return;

    std::lock(lhs.m, rhs.m);
    std::lock_guard<std::mutex>(lhs.m, std::adopt_lock);
    std::lock_gaurd<std::mutex>(rhs.m, std::adopt_lock);
    swap(lhs.some_detail, rhs.some_detail);
  }
};

int main(int argc, char** argv)
{
  return 0;
}
