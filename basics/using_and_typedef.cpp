// typedef and using have the same sematics.
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
typedef int MyInt;  // old
using NewInt = int; // similar to variable assignment, more readable.

// how to define a function type ?
typedef void (MyFunc)(int, int);
using NewFunc = void(int, int);

// define a function reference type ?
typedef void (&RefFunc)(int, int);
using NewRefFunc = void (&)(int, int);

void foo(int a, int b) {

}

////////////////////////////////////////////////////////////////////////////////
// typedef template class.
template <typename T> struct whatever {};

template <typename T> struct rebind {
  typedef whatever<T> type;
};

rebind<int>::type variable;
template <typename U> struct bar { typename rebind<U>::type _var_member; };

// use `using`
template <typename T> using my_type = whatever<T>;

my_type<int> new_variable;
template <typename U> struct baz { my_type<U> _var_member; };

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
  MyInt i1 = 1;
  NewInt i2 = 2;

  MyFunc f1;
  NewFunc f2;

  RefFunc rf = foo;
  NewRefFunc nrf = foo;
  rf(1, 2);
  nrf(1, 2);

  //////////////////////////////////////////////////////////////////////////////
  // typedef a pointer, most time it's a bad idea.
  typedef int* intptr;
  int y = 5;
  const intptr x = &y; // the pointer is const, it's equal to const (int *) ptr;
  std::cout << "x: " << *x << ", y: " << y << '\n';
  *x = 10;
  // int z = 20;
  // x = &z; // illegal
  std::cout << "x: " << *x << ", y: " << y << '\n';

  return 0;
}
