////////////////////////////////////////////////////////////////////////////////
// decltype keyword
////////////////////////////////////////////////////////////////////////////////
#include <iostream>

struct A { double x; };
const A* a;

decltype(a->x) y;       // type of y is double (declared type)
decltype((a->x)) z = y; // type of z is const double& (lvalue expression)

template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u) { // return type depends on template
  return t + u;                         // parameter return type can be deduced
}                                       // since C++14.

////////////////////////////////////////////////////////////////////////////////
decltype(auto) f1()
{
  int x = 0;
  return x; // decltype(x) is int, so f1 returns int.
}

decltype(auto) f2()
{
  int x = 0;

  // there will be a warning about reference to stack memory, it's undefined behavior.
  return (x); // decltype((x)) is int&, so f2 returns int&.
}
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  {
    int i = 33;
    decltype(i) j = i * 2;

    std::cout << "i = " << i << ", "
      << "j = " << j << std::endl;

    auto f = [] (int a, int b) -> int
    {
      return a * b;
    };

    decltype(f) g = f; // the type of lambda function is unique and unnamed
    i = f(2, 2);
    j = g(3, 3);

    std::cout << "i = " << i << ", "
      << "j = " << j << std::endl;

    decltype(i) k = add(i, j);

    std::cout << "i = " << i << ", "
      << "j = " << j << ". i + j = "
      << k << std::endl;
  }

  {
    // int& x = f1(); // error, couldn't bind to a temporary of type 'int'
                     // because f1() is a rvalue.

    int& x1 = f2(); // what about now ? it works fine.
  }

  return 0;
}

