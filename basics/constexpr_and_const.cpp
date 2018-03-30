///////////////////////////////////////////////////////////////////////////////
//
// `constexpr` is c++11 standardation.
//
// The advantage of constexpr ?
// make sematics more abvious
//
// Summary:
// using constexpr when function returns a constexpr.
// using const when the object is constant, although constexpr works fine.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

constexpr int sqr1(int arg)
{ return arg * arg; }

int sqr2(int arg)
{ return arg * arg; }

const     double PI1 = 3.1415926;
constexpr double PI2 = 3.1415926;

// constexpr double PI3 = PI1; // error, PI1 is not 'constexpr'
// constexpr double PI3 = PI2; // ok

///////////////////////////////////////////////////////////////////////////////
//
// A recursive function never returns constexpr

int fibonacci(int n)
{
  if (n == 0 || n == 1)
    return n;

  return fibonacci(n - 1) + fibonacci(n - 2);
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
//  std::cout << "9^2 = " << sqr1(9) << std::endl;
//  std::cout << fibonacci(10) << std::endl;

  return 0;
}
