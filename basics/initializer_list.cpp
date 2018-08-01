////////////////////////////////////////////////////////////////////////////////
//
// initializer_list
//
// The cost of std::initailizer_list ?
// Maybe create temporary array to store data, which needs copy all data the
// temporary array.
//
// References
// [1] Andrzej. 2016. The cost of std::initializer_list.
// https://akrzemi1.wordpress.com/2016/07/07/the-cost-of-stdinitializer_list/
//
////////////////////////////////////////////////////////////////////////////////
#include <initializer_list>
#include <vector>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// std::initializer_list takes only one type parameter,
// if you need different types, use variadic templates instead.
void values(std::initializer_list<int> intValues)
{
  std::cout << "Initializer list having " << intValues.size() << std::endl;

  typedef std::initializer_list<int>::const_iterator il_iter;
  il_iter begin = intValues.begin();
  for (; begin != intValues.end(); ++begin)
    std::cout << "Value: " << *begin << "\n";
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Make sure all element is copyable using std::initializer_list
struct Foo {
  Foo() {}
  Foo(std::initializer_list<Foo>) {
    std::cout << "initialier list" << std::endl;
  }
  Foo(const Foo&) {
    std::cout << "copy constructor" << std::endl;
  }
};
////////////////////////////////////////////////////////////////////////////////

template <typename Iter>
void print(Iter begin, Iter end)
{
  while (begin != end)
    std::cout << *begin++ << ' ';
  std::cout << '\n';
}

int main(int argc, char** argv)
{
  values({1, 2, 3, 4, 5, 6});  // Ok
  // values({1, 2.0}); error: narrowing conversion, from double to int
  // values(1, 2, 3, 4, 5, 6);  Error, it's variadic parameter

  Foo a;
  Foo b(a); // copy constructor
  Foo c{a}; // copy constructor -> initialier list

  // std::vector has the copy constructor and operator= with initializer_list
  std::vector<int> vi{1, 2, 3, 4, 5, 6};
  std::vector<int> vi1 = {1, 2, 3, 4, 5, 6};

  print(begin(vi), end(vi));
  print(begin(vi1), end(vi1));

  // auto keyword with initializer_list
  auto x = { 1, 2, 3, 4 }; // x's type is std::initializer_list<int>
  print(x.begin(), x.end());

  return 0;
}
