#include <iostream>

int main(int argc, char *argv[])
{
  // The `decltype(auto)` type-specifiers also deduces a type like `auto` does.
  // However, it deduces return types while keeping their references or
  // "const-ness", while `auto` will not.
  const int x = 0;
  auto x1 = x; // int
  decltype(auto) x2 = x; // const int

  int y = 0;
  int& y1 = y;
  auto y2 = y1; // int
  decltype(auto) y3 = y1; // int &
  int&& z = 0;
  auto z1 = std::move(z);
  decltype(auto) z2 = std::move(z); // int&&

  return 0;
}
