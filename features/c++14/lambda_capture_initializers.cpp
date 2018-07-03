#include <iostream>
#include <memory>

int factory(int i) {
  return i * 10;
}

int main(int argc, char *argv[])
{
  auto f = [x = factory(2)] { return x; };
  std::cout << f() << '\n'; // 20

  auto generator = [x = 0] () mutable {
    // this would not complile without 'mutable' as we are modifying x on each call
    return x++;
  };

  auto a = generator();
  auto b = generator();
  auto c = generator();

  std::cout << a << '\n'; // 0
  std::cout << b << '\n'; // 1
  std::cout << c << '\n'; // 2

  auto p = std::make_unique<int>(1);

  // auto task1 = [=] { *p = 5; }; // ERROR: std::unique_ptr cannot be copied.
  auto task2 = [p = std::move(p)] { *p = 5; };
  // okay, p is move-constucted into the closure object.
  // the original p is empty after task2 is created.

  return 0;
}
