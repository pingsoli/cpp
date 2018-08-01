////////////////////////////////////////////////////////////////////////////////
// from effective modern cpp item 4: Know how to view deduced types.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

template <typename T>
class TD;

int main(int argc, char *argv[])
{
  const int theAnswer = 42;

  auto x = theAnswer;
  auto y = &theAnswer;

  // compile, you will get the error information.
  // TD<decltype(x)> xType;
  // TD<decltype(y)> yType;

  // error information.
  // know_variable_type.cpp:16:19: error: implicit instantiation of undefined template
  //       'TD<int>'
  //   TD<decltype(x)> xType;
  //                   ^
  // know_variable_type.cpp:6:7: note: template is declared here
  // class TD;
  //       ^
  // know_variable_type.cpp:17:19: error: implicit instantiation of undefined template
  //       'TD<const int *>'
  //   TD<decltype(y)> yType;
  //                   ^
  // know_variable_type.cpp:6:7: note: template is declared here
  // class TD;
  //       ^
  // 2 errors generated.

  // sometimes it's hard to understand.
  std::cout << typeid(x).name() << '\n';  // i
  std::cout << typeid(y).name() << '\n';  // PKi

  return 0;
}
