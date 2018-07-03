#include <iostream>

// auto f(int i) {
//   return i;
// }

template <typename T>
auto& f(T& t) {
  return t;
}

int main(int argc, char *argv[])
{
  // Return a reference to a deduced type.
  auto g = [] (auto& x) -> auto& { return f(x); };
  int y = 123;
  int& z = g(y);

  std::cout << z << '\n';
  
  return 0;
}
