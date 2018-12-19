#include <iostream>

// name look up

// void foo(int) { std::cout << "void foo(int)" << '\n';}
//
// namespace X
// {
//   void foo() {
//     std::cout << "void X::foo()" << '\n';
//   }
//
//   void bar() {
//     foo(42); // ERROR: will not find `::foo`
//     // because `X::foo` hides it.
//   }
// }

struct Base {
  virtual void foo(int i) { std::cout << "Base::foo(int)" << '\n'; }
};

struct Derived : public Base {
  void foo() { std::cout << "Derived::foo()" << '\n'; }
  void bar() {
    foo(42); // will not find `Base::foo`
    // because `Derived::foo` hides it.
  }
};

int main(int argc, char *argv[])
{
  {
    // X::bar();
  }

  {
    Base base;
    Derived derived;

    derived.bar();
  }

  return 0;
}
