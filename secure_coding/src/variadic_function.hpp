#include <type_traits>

/*
 * Do not define a C-Style variadic funtion
 *
 * Problem: Calling the function without passing the value 0 as
 *          an arugument(after the first two argumetns) results in
 *          undefined behavior. Furthermore passing any type other
 *          than an int also results in undefined behivor.
 *
 * int add(int first, int second, ...)
 * {
 *    int r = first + second;
 *    va_list va;
 *    va_start(va, second);
 *
 *    while (int v = va_arg(va, int))
 *    {
 *      r += v;
 *    }
 *
 *    va_end(va);
 *    return r;
 * }
 *
 */

// Recursive Pack Expansion
//template <typename Arg,
//          typename std::enable_if<std::is_integral<Arg>::value>::type* = nullptr>
//int add(Arg f, Arg s) { return f + s; }
//
//template <typename Arg, typename... Ts,
//          typename std::enable_if<std::is_integral<Arg>::value>::type* = nullptr>
//int add(Arg f, Ts... rest) {
//  return f + add(rest...);
//}

// Braced Initialier Expansion
template <typename Arg, typename... Ts,
          typename std::enable_if<std::is_integral<Arg>::value>::type* = nullptr>
int add(Arg i, Arg j, Ts... all)
{
  int values[] = { j, all... };
  int r = i;

  for (auto v : values)
    r += v;

  return r;
}
