////////////////////////////////////////////////////////////////////////////////
// variable length and type of arguments of function ?
// passing different type of arguments ?
// ellipsis
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <type_traits>

#define USE_C   0
#define USE_C11 0

#if USE_C
#include <cstdarg>
////////////////////////////////////////////////////////////////////////////////
//
// Stop defining a C-Style variadic funtion
//
// Problem: Calling the function without passing the value 0 as
//          an arugument(after the first two argumetns) results in
//          undefined behavior. Furthermore passing any type other
//          than an int also results in undefined behivor.
//
int add(int count, ...)
{
   int r = 0;
   va_list va;

   va_start(va, count);
   for (int i = 0; i < count; ++i) {
     r += va_arg(va, int);
   }
   va_end(va);

   return r;
}
#elif
// Recursive Pack Expansion
template <typename Arg,
          typename std::enable_if<std::is_integral<Arg>::value>::type* = nullptr>
int add(Arg f, Arg s) { return f + s; }

template <typename Arg, typename... Ts,
          typename std::enable_if<std::is_integral<Arg>::value>::type* = nullptr>
int add(Arg f, Ts... rest) {
  return f + add(rest...);
}
#endif

////////////////////////////////////////////////////////////////////////////////
// Braced Initialier Expansion, only support same type.

#if USE_C11
// c++11
template <typename Arg, typename... Ts,
         typename std::enable_if<std::is_integral<Arg>::value>::type* = nullptr>
int add_m(Arg i, Arg j, Ts... all)
{
  int values[] = { j, all... };
  int r = i;

  for (auto v : values)
    r += v;

  return r;
}
#else
// c++14
template <typename Arg, typename... Ts,
         typename std::enable_if_t<std::is_integral<Arg>::value>* = nullptr>
int add_m(Arg i, Arg j, Ts... all)
{
  int values[] = { j, all... };
  int r = i;

  for (auto v : values)
    r += v;

  return r;
}
#endif

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
  int result = 0;
  // c legacy
  // result = add(6, 1, 2, 3, 4, 5, 6);
  // std::cout << result << std::endl;

  // c++
  result = add(1, 2, 3, 4, 5, 6);
  std::cout << result << std::endl;

  // brace-closing initializer list
  result = add_m(1, 2, 3, 4, 5, 6);
  std::cout << result << std::endl;

  // error no matching function
  // result = add(1, 23, "hello");

  return 0;
}
