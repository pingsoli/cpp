////////////////////////////////////////////////////////////////////////////////
// tag dispatch
// SFINAE -> Substitution Is Not An Error
//
// the following example just give the concept, not implement totally.
//
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <type_traits>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// tag dispatch

// template <typename T>
// bool equals(T lhs, T rhs, true_type) // floating
// {
//   // imprecision handling, it's ignored, return true directly.
//   return true;
// }
//
// template <typename T>
// bool equals(T lhs, T rhs, false_type) // nonfloating
// {
//   return lhs == rhs;
// }
//
// template <typename T>
// bool equals(T lhs, T rhs)
// {
//   return equals(lhs, rhs,
//       conditional_t<is_floating_point<T>::value, true_type, false_type>{});
// }

////////////////////////////////////////////////////////////////////////////////
// SFIANE

// template <typename T,
//          typename = enable_if_t<!is_floating_point<T>::value>>
// bool equals(T lhs, T rhs)
// {
//   return lhs == rhs;
// }

// template <typename T,
//          typename = enable_if_t<is_floating_point<T>::value>>
// bool equals(T lhs, T rhs)
// {
//   return lhs == rhs;
// }

// template <typename T>
// bool equals(T lhs, T rhs, enable_if_t<!is_floating_point<T>::value>* = nullptr)
// {
//   return lhs == rhs;
// }
//
// template <typename T>
// bool equals(T lhs, T rhs, enable_if_t<is_floating_point<T>::value>* = nullptr)
// {
//   // handles imprecision
//   return true;
// }

template <typename T>
enable_if_t<!is_floating_point<T>::value, bool> equals(T lhs, T rhs)
{
  return lhs == rhs;
}

template <typename T>
enable_if_t<is_floating_point<T>::value, bool> equals(T lhs, T rhs)
{
  // handles imprecision, ignored
  return true;
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  std::cout << equals(1, 1) << '\n'; // true
  std::cout << equals(1.0, 1.0) << '\n'; // true
  std::cout << equals(1.0f, 1.0f) << '\n'; // true
  std::cout << equals(2.0f - 0.2f, 1.8f) << '\n'; // true

  std::cout << equals(0.42 - 0.4, 0.4) << '\n'; // false

  // 0.42 - 0.4 == 0.2 is not equal ?
  // there are two ways to solve it.
  // 1) tag dispatch
  // 2) SFINAE

  return 0;
}
