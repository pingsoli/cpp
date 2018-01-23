#include <iostream>
#include "variadic_function.hpp"

int main(int argc, char **argv)
{
  int result = add(1, 2, 3, 4, 5, 6);
  std::cout << result << std::endl;

  // brace-closing initializer list
  result = add(1, 2, 3, 4, 5, 6);
  std::cout << result << std::endl;

  // Get an error, must be int type
  // result = add(1, 23, "hello");

  return 0;
}
