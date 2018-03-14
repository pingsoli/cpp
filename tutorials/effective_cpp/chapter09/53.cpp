///////////////////////////////////////////////////////////////////////////////
//
// Item 53: Pay attention to compiler warnings.
//
// Things to remember
//
// 1) Take compiler warnings seriously, and strive to compile warning-free at
// the maximum warning level supported by your compilers.
//
// 2) Don't become dependent on compiler warnings, because different compilers
// warn about different things. Porting to a new compiler may eliminate
// warning messages you've come to rely on.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

class B {
public:
  virtual void f() const {
    std::cout << "B::f()" << std::endl;
  }
};

class D : public B {
public:
  virtual void f() {
    std::cout << "D::f()" << std::endl;
  }
};

int main(int argc, char** argv)
{
  B* b = new D;

  // g++ won't give any warning
  b->f();  // B::f()

  // if you want to polymorphism you have to get rid of const in class B's f

  return 0;
}
