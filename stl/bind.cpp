////////////////////////////////////////////////////////////////////////////////
// lambda expression is easier than std::bind sometimes.
//
// std::bind can use when you don't know the actual arguments at compile-time,
// but have to create a callable object with arguments runtime.
// it can be used to reorder arguments.
////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <vector>
#include <memory>
#include <iostream>

void f(int n1, int n2, int n3, const int& n4, int n5) {
  std::cout << n1 << ' ' << n2 << ' ' << n3 << ' '
    << n4 << ' ' << n5 << '\n';
}

int g(int n1) {
  return n1;
}

struct Foo {
  void print_sum(int n1, int n2) {
    std::cout << n1 + n2 << '\n';
  }

  int data = 10;
};

int main(int argc, char *argv[])
{
  using namespace std::placeholders;

  int n = 7;
  auto f1 = std::bind(f, _2, _1, 42, std::cref(n), n);
  n = 10;
  f1(1, 2, 101); // f(2, 1, 42, n, 7)

  auto f2 = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);
  f2(10, 11, 12); // f(12, g(12), 12, 4, 5)

  Foo foo;
  auto f3 = std::bind(&Foo::print_sum, &foo, 95, _1);
  f3(5);

  // bind to a pointer to data member
  // auto f4 = std::bind(&Foo::data, 1);
  // std::cout << f4(foo) << '\n';

  return 0;
}
