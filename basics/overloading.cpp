#include <iostream>

struct Foo {};
struct Bar {};

void print(const Foo& foo) {
  std::cout << "foo" << '\n';
}

void print(const Bar& bar) {
  std::cout << "bar" << '\n';
}

void test(int i) {}
void test(int i, double d) {}
void test(int i, float f, double d) {}

// ERROR: ambiguating new declaration.
// int test(int i) { return 0; } // overloading does not care the return type.

int main(int argc, char *argv[])
{
  Foo foo;
  Bar bar;

  print(foo);
  print(bar);

  return 0;
}
