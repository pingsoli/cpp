///////////////////////////////////////////////////////////////////////////////
//
// Item 48: Be aware of template metaprogramming.
//
// TMP: smaller executables, shorter runtimes, less memory requirements.
// but, the compilation takes longer.
//
// Things to remember
//
// 1) Template metaprogramming can shift work from runtime to compile-time,
// thus enabling earlier error detection and higher runtime performance.
//
// 2) TMP can be used to generate custom code based on combinations of policy
// choices, and it can also be used to avoid generating code inappropriate for
// particular types.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

template <unsigned n>
struct Factorial {
  enum { value = n * Factorial<n-1>::value };
};

template <>
struct Factorial<0> {
  enum { value = 1 };
};

int main(int argc, char** argv)
{
  std::cout << Factorial<5>::value << std::endl;
  std::cout << Factorial<10>::value << std::endl;

  return 0;
}
