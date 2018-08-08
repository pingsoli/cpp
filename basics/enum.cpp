// unscoped enums and scoped enums

#include <iostream>

// C++98-style enums
// enum Color { black, white, red };
// auto black = false; // error! black already declared in this scope.

// c++11 enum class.
enum class Color { black, white, red };
auto white = false; // it's fine.

// more detail: namespace.cpp

int main(int argc, char *argv[])
{
  Color w = Color::white;
  auto b = Color::black;

  // convert enum class member to a integer.
  std::cout << static_cast<int>(Color::black) << '\t'
            << static_cast<int>(Color::red)   << '\t'
            << static_cast<int>(Color::white) << '\n';

  return 0;
}
