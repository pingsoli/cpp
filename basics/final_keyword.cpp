// Avoid inherited from my class ?
// add final specifier behind base class name.
//
// Avoid derived class override member function ?
// add final specifier to member function of base class.
//
// Note: put `final` specifier behind function name or class name.

#include <iostream>


// struct ForbidInheriteFrom final {
// };
//
// struct Test : public ForbidInheriteFrom { // won't compile
// };


struct Base {
  virtual void foo() final { std::cout << "Base::foo()" << '\n'; }
};

struct Derived : public Base {
  // virtual void foo() { std::cout << "Derived::foo()" << '\n'; }
};


int main(int argc, char *argv[])
{
  {
    // forbid inherited from base class
  }

  {
    // forbid derived class override member function
    Base *p = new Derived;
    p->foo();
  }

  return 0;
}
