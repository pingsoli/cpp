///////////////////////////////////////////////////////////////////////////////
//
// mutable keyword in c++
//
// Usage
// 1) Denote lambda expression, to make by-value captures modifiable.
// 2) Make class member modifiable even when the class itself is const. like
// mutex exmple
//
// References
// [1] https://www.quora.com/When-should-I-actually-use-a-mutable-keyword-in-C++
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

struct X
{
  mutable int mi;
  std::string s;

  X(const std::string& str):
    s{str}, mi{0}
  {}
};

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////
  //
  // Make by-value captures modifiable.

  {
    int i = 0;

    auto a1 = [=] () mutable { i = 42; };  // ok
//    auto a2 = [=] ()         { i = 42; };  // error

    a1();
//    a2();

    std::cout << i << std::endl; // x == 0
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  // Make class member modifiable even when the class itself is const

  {
    const X x("hello");
    x.mi = 41;     // ok, because it's mutable
//    x.s = "world"; // error

    std::cout << x.mi << ' ' << x.s << std::endl;
  }

  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
