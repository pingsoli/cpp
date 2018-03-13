///////////////////////////////////////////////////////////////////////////////
//
// Item 33: Avoid hiding inherited names.
//
// Things to remember:
// 1) Names in derived classes hide names in base classes. Under public
// inheritance, this is never desirable.
//
// 2) To make hidden names visible again, employ using declarations or
// forwording functions.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

class Base
{
public:
  virtual void mf1() = 0;

  virtual void mf1(int x) {
    std::cout << "void Base::mf1(int x)" << std::endl;
  }

  virtual void mf2() {
    std::cout << "void Base::mf2()" << std::endl;
  }

  void mf3() {
    std::cout << "void Base::mf3()" << std::endl;
  }

  void mf3(double d) {
    std::cout << "void Base::mf3(double d)" << std::endl;
  }

private:
  int x;
};

class Derived : public Base
{
public:
  /////////////////////////////////////////////////////////////////////////////

  // Magic is here, make all things in Base named mf1 and mf3 visible
  // (and public) in Derived's scope.
  using Base::mf1;
  using Base::mf3;

  /////////////////////////////////////////////////////////////////////////////

  virtual void mf1() {
    std::cout << "void Derived::mf1()" << std::endl;
  }

  void mf3() {
    std::cout << "void Derived::mf3()" << std::endl;
  }

  void mf4() {
    std::cout << "void Derived::mf4()" << std::endl;
  }
};

int main(int argc, char** argv)
{
  Derived d;
  int x;

  d.mf1(); // Derived::mf1
  d.mf1(x); // error, Derived::mf1 hides Base::mf1
  d.mf2(); // Base::mf2
  d.mf3(); // Derived::mf3
  d.mf3(x); // error, Derived::mf3 hides Base::mf3

  return 0;
}
