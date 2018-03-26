///////////////////////////////////////////////////////////////////////////////
//
// Order of evaluation of arguments to a function call is unspecified
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

void foo(int a, int b)
{
  std::cout << a << ", " << b << std::endl;
}

int get_num()
{
  static int i = 0;
  return ++i;
}

int main(int argc, char** argv)
{
  foo(get_num(), get_num()); // calls to get_num() are unordered
  return 0;
}
