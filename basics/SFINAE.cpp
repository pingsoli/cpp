////////////////////////////////////////////////////////////////////////////////
// tag dispatch
// SFINAE -> Substitution Failure Is Not An Error
//
// What is SFINE ?
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

// Check class whether contains specific functions ?
#include <utility>

template<typename T>
struct has_member_foo
{
private:
  template<typename U>
    static auto Check(int) -> decltype(std::declval<U>().foo(), std::true_type());
  template<typename U>
    static std::false_type Check(...);

public:
  enum { value = std::is_same<decltype(Check<T>(0)), std::true_type>::value };
};

struct Test {
  void foo() { std::cout << "Test::foo()" << '\n'; }
};

struct AnotherTest {
  void test() { std::cout << "AnotherTest::test()" << '\n'; }
};

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

  {
    // check class whether has member function ?
    if (has_member_foo<Test>::value) {
      std::cout << "Test has foo function" << '\n';
    } else {
      std::cout << "Test has not foo function" << '\n';
    }

    if (has_member_foo<AnotherTest>::value) {
      std::cout << "AnotherTest has foo function" << '\n';
    } else {
      std::cout << "AnotherTest has not foo function" << '\n';
    }
  }

  return 0;
}
