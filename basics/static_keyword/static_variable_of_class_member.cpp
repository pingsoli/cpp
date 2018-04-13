#include <iostream>

class MyClass {
  static int n;

public:
  void increase_n(int increment) {
    n += increment;
  }

  void print_n() const {
    std::cout << n << '\n';
  }
};

// initialize static member variable
int MyClass::n = 10;

int main(int argc, char** argv)
{
  MyClass c;

  c.increase_n(10);
  c.print_n();

  c.increase_n(20);
  c.print_n();

  return 0;
}
