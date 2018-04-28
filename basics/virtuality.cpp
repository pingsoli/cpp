////////////////////////////////////////////////////////////////////////////////
//
// virtuality
//
// what if the base calss destructor is non-virtual ? like the following.
//
// Base *p = new Derived();
// delete p;  // what happen ?
//
// undefined behavior, may lead to memory leak.
//
// Problem
// memory leak. some cleanning work in derived class.
//
// SUMMARY
// 1) A base class destructor should be either public and virtual, or protected
// and nonvirtual.
// 2) Prefer to make interfaces nonvirtual.
//
// References
// [1] http://www.gotw.ca/publications/mill18.htm
// [2] https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Base class destructor is public and virtual.
struct Base {
  virtual ~Base() {
    std::cout << "Base destructor" << std::endl;
  }

  // A comm interface
  void foo() {
    std::cout << "Base class interface ...\n";
    bar();
  }

private:
  // base class implementation
  virtual void bar() {
    std::cout << "Base class bar function\n";
  }
};

struct Derived : public Base {
  virtual ~Derived() {
    std::cout << "Derived destructor" << std::endl;
  }

private:
  // derived class has their own implementation
  void bar() {
    std::cout << "Derived class bar function\n";
  }
};

// mutiple inheritance
struct Grand : public Derived {
  virtual ~Grand() {
    std::cout << "Grand destructor" << std::endl;
  }
};
////////////////////////////////////////////////////////////////////////////////
// Base class destructor is protected and nonvirtual
// now we cannot delete the pointer directly.
struct A {
protected:
  ~A() {
  std::cout << "~A" << std::endl;
  }
};

struct B : public A {
protected:
  ~B() {
    std::cout << "~B" << std::endl;
  }
};
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
//  {
//    Base *pd = new Derived();
//    Base *pg = new Grand();
//
//    pd->foo();
//
//    delete pg;
//
//    //  delete pd;
//  }

  return 0;
}
