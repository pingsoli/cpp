// Keep in mind, std::shared_ptr and std::weak_ptr are from
// boost library.
// shared_ptr
// auto_ptr
// weak_ptr

// RAII

#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <vector>

struct Shoe { ~Shoe() { std::cout << "Buckle my shoe\n"; }};

class MyClass {
  boost::scoped_ptr<int> ptr;

public:
  MyClass() : ptr{new int} { *ptr = 0; }
  int add_one() { return ++*ptr; }
};

// scoped_ptr::reset() function can destroy the allocated object
// the destructor of boost::scoped_ptr releases the referenced
// object with delete. It's noncopyable.
void test_scoped_ptr()
{
  // basics, manager raw pointer
  boost::scoped_ptr<int> p{new int{1}};
  std::cout << *p << '\n';

  // reset method to destroy the object, and manager new thing.
  p.reset(new int{2});
  std::cout << *p << '\n';

  // get method to get the raw pointer
  std::cout << *p.get() << '\n';
  p.reset();
  std::cout << std::boolalpha << static_cast<bool>(p) << '\n';

  // smart pointer, destroy automatically when out the scope
  boost::scoped_ptr<Shoe> x(new Shoe);

  MyClass my_instance;
  std::cout << my_instance.add_one() << std::endl;
  std::cout << my_instance.add_one() << std::endl;

  // use scoped_ptr to wrap std container
  std::vector<int> *pvec = new std::vector<int>{1, 2, 3};
  boost::scoped_ptr<std::vector<int>> spv{ pvec };

  // What will happen ? boost official website says
  // scoped_ptr should not be used in c++ stanadard library.
  // So, the following code is a bad try, never do it like this.
  // use shared_ptr and unique_ptr instead.
  typedef std::vector<int>::iterator viter_type;
  for (viter_type it = spv->begin(); it != spv->end(); ++it)
    std::cout << *it << " ";
  std::cout << '\n';
}

void test_scoped_array()
{
  boost::scoped_array<int> p{new int[2]};
  *p.get() = 1;
  p[1] = 2;
  p.reset(new int[3]);
}

// what's the difference between boost::scoped_ptr
// and boost::scoped_array ?
// scoped_ptr use delete to destructe the object,
// scoped_array use delete[] to destory the object.

void test_shared_ptr()
{
  boost::shared_ptr<int> p1{new int{1}};
  std::cout << *p1 << std::endl;

  boost::shared_ptr<int> p2{ p1 };
  p1.reset(new int{2});

  // get method, don't need to use it.
  std::cout << *p1.get() << std::endl;
  std::cout << *p2.get() << std::endl;
}

// smart_pointer bad practice
// Exception-safe and unsafe use of shared_ptr
//
// void ok()
// {
//   shared_ptr<int> p(new int(2));
//   f (p, g())
// }
//
// void bad()
// {
//   f ( shared_ptr<int>(new int(2)), g() )
// }

int main()
{
//  test_scoped_ptr();
//  test_scoped_array();
  test_shared_ptr();
}
