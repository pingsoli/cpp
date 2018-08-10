#include <type_traits>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// specialize class template

// primary templates
template <typename T>
struct is_pointer : std::false_type {};

// partial specialization, since the specialization has template parameter.
template <typename T>
struct is_pointer<T*> : std::true_type {};
////////////////////////////////////////////////////////////////////////////////
// know the differences between overloading and specialization

template <typename T1, typename T2>
T1 max(const T1& a, const T2& b) {
  return (a < b ? b : a);
}

// think about that ? is it specializtion ?
// It's overloading
template <typename T>
T max(const T& a, const T& b) {
  return (a < b ? b : a);
}

// this is specializtion, but this won't compile, because template function
// don't support partial specialization.
// template <typename T>
// T max<T, T>(const T& a, const T& b) {
//   return (a < b ? b : a);
// }

int main(int argc, char *argv[])
{
  std::cout << max(1, 2.0) << '\n';
  std::cout << max(1, 2) << '\n';
  std::cout << max(2.0f, 3.0) << '\n';

  return 0;
}
