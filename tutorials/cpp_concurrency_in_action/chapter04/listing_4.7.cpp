///////////////////////////////////////////////////////////////////////////////
//
// Passing arguments to function with std::async
//
///////////////////////////////////////////////////////////////////////////////

#include <future>
#include <string>
#include <iostream>

struct X
{
  void foo(int i, const std::string& name)
  {
    std::cout << "X::foo(int, const std::string&)" << std::endl;
  }

  std::string bar(const std::string& name)
  {
    return name;
  }

  void operator()(const X& x)
  {
    std::cout << "X::operator()" << std::endl;
  }
};

struct Y
{
  double operator()(double d)
  {
    return 0.0;
  }
};

class move_only
{
public:
  move_only() = default;
  move_only(move_only&&)
  {}
  move_only& operator=(move_only&&)
  {}

  move_only(const move_only&) = delete;
  move_only& operator=(const move_only&) = delete;

  void operator()()
  {}
};

int main(int argc, char** argv)
{
  X x;
  auto f1 = std::async(&X::foo, &x, 42, "foo");
  auto f2 = std::async(&X::bar, x, "bar");

  Y y;
  auto f3 = std::async(Y(), 3.141);
  auto f4 = std::async(std::ref(y), 3.12);

  X baz;

  auto f5 = std::async(move_only());

  auto f6 = std::async(std::launch::async, Y(), 1.2); // Run in new thread

  // Run in wait() and get()
  auto f7 = std::async(std::launch::deferred, baz, std::ref(x));
  auto f8 = std::async(
      std::launch::deferred | std::launch::async,
      baz, std::ref(x));

  auto f9 = std::async(baz, std::ref(x));
  f7.wait(); // Invoke deferred function

  return 0;
}
