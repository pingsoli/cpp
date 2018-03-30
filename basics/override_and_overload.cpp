///////////////////////////////////////////////////////////////////////////////
//
// Override Vs. Overload
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

///////////////////////////////////////////////////////////////////////////////
//
// Overide

void do_something()
{
  std::cout << "void do_something()" << std::endl;
}

// it's ambiguous with void do_something()
//
// int do_something()
// {
//   std::cout << "int do_something()" << std::endl;
//   return 10;
// }

void do_something(int)
{
  std::cout << "void do_something(int)" << std::endl;
}

int do_something(int, float)
{
  std::cout << "int do_something(int, float)" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
//
// Override

struct Base
{
  virtual void func() {
    std::cout << "Base::func()" << std::endl;
  }

  // only declaration, no definition.
  virtual void func(int) {
    std::cout << "Base::func(int)" << std::endl;
  }

  // no virtual keyword, it's not polymorphism
  void foo() {
    std::cout << "Base::foo()" << std::endl;
  }

  // pure virtual function, must be implemented by derived class
//  virtual void bar() = 0;
};

struct Derived : public Base
{
  void func() {
    std::cout << "Derived::func()" << std::endl;
  }

  void func(int) {
    std::cout << "Derived::func(int)" << std::endl;
  }

  void foo() {
    std::cout << "Derived::foo()" << std::endl;
  }

  void bar() {
    std::cout << "void Derived::bar()" << std::endl;
  }
};

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{

  /////////////////////////////////////////////////////////////////////////////
  //
  // overload

//  int i = do_something();
//  do_something();
//  do_something(1);
//  do_something(1, 2.3f);

  /////////////////////////////////////////////////////////////////////////////
  //
  // override

  Base* pd = new Derived;
//  pd->func();
//  pd->foo();  // static binding, Base::foo()
//  pd->bar();
//
  Base* pb = new Base;
//  pb->func();

  Base    base;
  Derived derived;

//  base.foo();    // no virtual, static type, Base::foo()
//  derived.foo(); // static type, Base::foo()

  Derived* ppd = new Derived;
  ppd->foo();  // Derived::foo()

  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
