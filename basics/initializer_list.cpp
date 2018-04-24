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
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// std::initializer_list takes only one type, if you need different types,
// use variadic templates instead.
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
// std::initializer_list needs all element is copyable.
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

int main(int argc, char** argv)
{
  values({1, 2, 3, 4, 5, 6});  // Ok
//  values({1, 2.0}); // error: narrowing conversion, from double to int
//  values(1, 2, 3, 4, 5, 6);  // Error, it's variadic parameter

  Foo a;
  Foo b(a); // copy constructor
  Foo c{a}; // copy constructor -> initialier list

  return 0;
}
