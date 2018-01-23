// Item 2: Prefer consts, enums, and inlines to #defines
// 1) For simple constants, prefer const objects or enums to #defines
// 2) For function-like macros, prefer inline functions to #defines

#include <iostream>
#include <string>
#include "game_player.h"

// It's very hard to debug, why?
// ASPECT_RATIO may not get entered into the symbol table.
#define ASPECT_RATIO 1.653

// The solution is to replace the macro with a constant.
const double aspect_ratio = 1.653;

const char* const name = "pingsoli";

// Use std::string instead
const std::string myName("pingsoli");

#define MAX(a,b) ((a) > (b) ? (a) : (b))

template <typename T>
inline const T& max(const T& a, const T& b)
{
  return a > b ? a : b;
}

int main(int argc, char **argv)
{
// std::cout << ASPECT_RATIO << std::endl;
// std::cout << aspect_ratio << std::endl;

  GamePlayer g;
  std::cout << "static const: " << g.getTurns() << std::endl;
  std::cout << "enum: " << g.getAnotherTurns() << std::endl;

  // nomal
  std::cout << "1 and 3, bigger is: " << max(1, 3) << std::endl;

  int a = 2;
  int b = 2;
  std::cout << a << " and " << b << " bigger is: "
            << MAX(++a, b) << std::endl;
  // output like this:
  // 4 and 2 bigger is: 4
  // a is incremented twice 

  // now, it gets the right result
  int c = 4, d = 4;
  std::cout << c << " and " << d << " bigger is: "
            << max(++c, d) << std::endl;

  return 0;
}
