#include <string>
#include <iostream>
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////
// adder example
template <typename T>
T adder(T&& val) {
  return std::forward<T>(val);
}

template <typename T, typename... Args>
T adder(T&& a, Args&&... args) {
  return a + adder(std::forward<T>(args)...);
}
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  auto result = adder(1, 2, 3, 4, 5, 6, 7);
  auto str = adder<std::string>("hello", " world", ", hi", ", I'm comming.");

  std::cout << result << '\n';
  std::cout << str << '\n';

  return 0;
}
