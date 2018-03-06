/*
 * perfect forwarding
 */
#include <iostream>

///////////////////////////////////////////////////////////////////////////////

void foo(int& i) {
  i = 2;
  std::cout << "int& " << i << std::endl;
}

void foo(int&& i) {
  std::cout << "int&& " << i << std::endl;
}

template <typename T>
void func(T&& t)
{
  foo(std::forward<T>(t)); // invoke which function ?
}

///////////////////////////////////////////////////////////////////////////////

void foo(const int& i)
{
  std::cout << "const int& " << i << std::endl;
}

// Cannot distinguish between l-value and r-value
// so, func(const T& t) cannot wrap foo(int&) or foo(int&&) template funciton,
// only can wrap `foo(const int& )`.
template <typename T>
void func(const T& t)
{
  foo(t); // It's ok when implement `foo(const int&)`, otherwise wrong.
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  // test func(T&&) template function, comment func(const int&) and uncomment
  // func(T&&)
  int x = 10;
  func(x);  // func(int& i)
  func(1);  // func(int&& i)

  // test func(const T&) template function, comment func(T&&) and uncomment
  // func(const T&)
  func(x);  // func(const int&)
  func(1);  // func(const int&)

  return 0;
}
