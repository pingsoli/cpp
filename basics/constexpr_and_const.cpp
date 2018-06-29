///////////////////////////////////////////////////////////////////////////////
//
// `constexpr` is c++11 standardation.
//
// The advantage of constexpr ?
// It's explicit and strong.
//
// What does 'constexpr' mean ?
// constexpr variable is guaranteed to have a value available at compile time.
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

////////////////////////////////////////////////////////////////////////////////
// 'constexpr variable is guaranteed to have a value available at compile time.
const     double PI1 = 3.1415926;
constexpr double PI2 = 3.1415926;

// constexpr double PI3 = PI1; // error, PI1 is not 'constexpr'
// constexpr double PI3 = PI2; // ok

///////////////////////////////////////////////////////////////////////////////
// A recursive function never returns constexpr
int fibonacci(int n) {
  if (n == 0 || n == 1) return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

////////////////////////////////////////////////////////////////////////////////

class Test {
public:
  static const int a  = 3;
};

class Test1 {
public:
  static constexpr int a = 3;
};

int main(int argc, char** argv)
{
 //std::cout << "9^2 = " << sqr1(9) << std::endl;
 //std::cout << fibonacci(10) << std::endl;

  //////////////////////////////////////////////////////////////////////////////
  // run-time and compile-time variable ?
  // static const members or const variable could either mean a compile time
  // value or a runtime value. but constexpr only mean the variable is compile
  // time.

 //int run_time;
 //std::cin >> run_time;

 //static const int compile_time = run_time;
 //std::cout << compile_time;
  //////////////////////////////////////////////////////////////////////////////

  //std::cout << Test::a << std::endl; // ok, compile time value can have value.

  // error, compile time constants don't have address.
  //std::cout << Test::a << "(" << &Test::a << ")" << std::endl;

  return 0;
}
