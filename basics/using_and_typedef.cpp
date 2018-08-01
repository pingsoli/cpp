////////////////////////////////////////////////////////////////////////////////
// typedef and using have the same sematics.
//
// summary
// 1) prefer using than typedef.
// 2) typedef don't support templatization.
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <list>

////////////////////////////////////////////////////////////////////////////////
// alias variable type.
typedef
  std::unique_ptr<std::unordered_map<std::string, std::string>>
  UPtrMapSSOld;

using UPtrMapSS =
  std::unique_ptr<std::unordered_map<std::string, std::string>>;

// alias function.
typedef void (MyFunc) (int, int);
using NewFunc = void (int, int);

// alias function pointer.
typedef void (*Fp) (int, const std::string&);
using FP = void (*) (int, const std::string&);

// alias function reference.
typedef void (&RefFunc)(int, int);
using NewRefFunc = void (&)(int, int);

void foo(int a, int b) {
}

// alias template
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
  MyFunc f1;
  NewFunc f2;

  RefFunc rf = foo;
  NewRefFunc nrf = foo;
  rf(1, 2);
  nrf(1, 2);

  //////////////////////////////////////////////////////////////////////////////
  // typedef a pointer, it's a bad idea almost time.
  // typedef int* intptr;
  using intptr = int *;
  int y = 5;
  const intptr x = &y; // int * const x; x is const-pointer to non-const.
  const int *z = &y;
  const int w  = 20;

  std::cout << typeid(x).name() << '\n'; // Pi
  *x = 10;
  // *z = 20; // illegal
  // x = &w; // illegal

  return 0;
}
