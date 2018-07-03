// C++14 allows the auto type-specifier in the parameter list.
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
  auto identity = [] (auto x) { return x; };
  int three = identity(3);
  std::string foo = identity("foo");

  std::cout << three << '\n'; // 3
  std::cout << foo << '\n';   // foo

  return 0;
}
