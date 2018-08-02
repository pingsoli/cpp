///////////////////////////////////////////////////////////////////////////////
// `constexpr` is c++11 standardation.
//
// The advantage of constexpr ?
// It's explicit and strong.
//
// What does 'constexpr' mean ?
// constexpr indicates a value that's is not only a constant, it's known during
// compilation.
//
// constexpr guarantee the object is const, but constant object may not be
// constexpr.
//
// in C++11 and C++14
// if we specifiy a function with constexpr, that means the funtion will return
// a const value known at compile time.
// C++14 restrictions is more looser. the setter can be constexpr.
//
// Summary:
// using const when the object is constant, although constexpr works fine.
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <array>

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

////////////////////////////////////////////////////////////////////////////////

// return size of an array as a compile-time constant. (The arrary paramter
// has no name, because we care only about the number of elements it contains.)
template <typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept {
  return N;
}

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

  //////////////////////////////////////////////////////////////////////////////
  // constexpr is determined at compiling time.
  int keyVals[] = { 1, 2, 3, 4, 5, 6, 7 }; // keyVals has 7 elements.
  int mappedVals[arraySize(keyVals)];  // so does mappedVals.
  std::array<int, arraySize(keyVals)> newMappedVals; // so does newMappedVals.

  return 0;
}
