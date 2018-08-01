#include <iostream>
#include <iterator>
#include <deque>

// auto f(int i) {
//   return i;
// }

template <typename T>
auto& f(T& t) {
  return t;
}

// more complex example C++ 14 version
// return a container element reference.
// c[i] is reference to the real element.
template <typename Container, typename Index>
decltype(auto)
authAndAddress(Container&& c, Index i)
{
  // do something
  return std::forward<Container>(c)[i];
}

// how to do the same thing in c++11.
// template <typename Container, typename Index>
// auto authAndAddress(Container&& c, Index i)
//   -> decltype(std::forward<Container>(c)[i])
// {
//   // do something
//   return std::forward<Container>(c)[i];
// }

int main(int argc, char *argv[])
{
  // Return a reference to a deduced type.
  auto g = [] (auto& x) -> auto& { return f(x); };
  int y = 123;
  int& z = g(y);

  z = 100;
  std::cout << z << " " << y << '\n';

  // decltype(auto)

  std::deque<int> di = {1, 2, 3, 4, 5};
  authAndAddress(di, 3) = 10;
  std::copy(begin(di), end(di), std::ostream_iterator<int>(std::cout, " "));

  return 0;
}
