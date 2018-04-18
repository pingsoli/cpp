////////////////////////////////////////////////////////////////////////////////
//
// Pass a polymorphic object to an STL algorithm
//
////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

struct Base {
  int operator()(int) const {
    method();
    return 42;
  }

  virtual void method() const {
    std::cout << "Base class called.\n";
  }
};

struct Derived : public Base {
  void method() const override {
    std::cout << "Derived class called.\n";
  }
};

void func(const Base& base)
{
  std::vector<int> v = {1, 2, 3};

  std::transform(begin(v), end(v), begin(v), base);
  // output
  // Base class called.
  // Base class called.
  // Base class called.

  // lambda expression and pass by reference
  std::transform(begin(v), end(v), begin(v),
      [&base] (int n) {
        return base(n);
      });

  // the simplest and best solution is pass by reference
  std::transform(begin(v), end(v), begin(v), std::ref(base));
}

int main(int argc, char** argv)
{
  Derived d;
  func(d);

  return 0;
}
