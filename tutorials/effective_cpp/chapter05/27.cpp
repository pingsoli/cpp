///////////////////////////////////////////////////////////////////////////////
//
// Item 27: Minimize casting
//
///////////////////////////////////////////////////////////////////////////////
//
// Four casting template function
// static_cast, dynamic_cast, reinterpret_cast, const_cast
//
// 1) const_cast
//    cast away the constness of objects.
//
// 2) dynamic_cast
//    safe downcasting.
//
// 3) reinterpret_cast
//    for low-level casts.
//
// 4) static_cast
//    can be used to force implicit conversions.
//
///////////////////////////////////////////////////////////////////////////////
//
// 1) Avoid casts whenever pratical, especially dynamic_casts in performance
// sensitive code. If a design requires casting, try to develop a cast-free
// alternative.
//
// 2) When casting is nessary, try to hide it inside a function. Clients can
// then call the function instead of putting casts in their own code.
//
// 3) Prefer C++-style casts to old-style casts. They are easier to see, and
// they are more specific about what they do.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

class Widget
{
public:
  explicit Widget(int size)
    : size_{size}
  { }

private:
  int size_;
};

void doSomething(const Widget& w)
{
  std::cout << "do something" << std::endl;
}

class Base
{
};

class Derived : public Base
{
};

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////

  // static_cast enforce implicit conversion
  doSomething(static_cast<Widget>(15));

  //  doSomething(15); // error

  int x = 1, y = 2;
  double d = static_cast<double>(x) / y;
  std::cout << d << std::endl;

  /////////////////////////////////////////////////////////////////////////////

  // both size is one byte
  std::cout << "Base " << sizeof(Base) << std::endl;
  std::cout << "Derived " << sizeof(Derived) << std::endl;

  ////////////////////////////////////////////////////////////////////////////

  return 0;
}
