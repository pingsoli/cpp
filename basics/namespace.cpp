// FAQ:
// Q: What namespace do?
// A: Sloving the problem of conflict names.
//
// Tips:
// 1) Specify namespace name explictly, avoid the automatic lookup.
//       pingsoli::cos(d);
//
// 2) Alias namespace name when it is too long.
//       namespace CV = CppAnnotation::Virtual;
//       using namespace CV;
//
////////////////////////////////////////////////////////////////////////////////
// Example:
// // file1.cpp
// namespace pingsoli {
//   double cos(double degres) {
//     ...
//   }
// }
//
// // file2.cpp
// namespace pingsoli {
//   double sin(double degres) {
//     ...
//   }
// }
//
// // header.h
// namespace pingsoli
// {
//   double cos(double);
//   double sin(double);
// }
////////////////////////////////////////////////////////////////////////////////
// namespace lookup
//
// // 'Koening lookup'
// fun(pingsoli::FIRST);
//
// pingsoli::fun(pingsoli::FIRST)

#include <iostream>

// #define FIRST 1
// #define SECOND 2

const int FIRST = 10;
const int SECOND = 20;

namespace pingsoli {

  // const int FIRST = 100;
  const int SECOND = 200;

  enum Value {
    FIRST  // conflict with macro `#define FIRST 1`
           // conflict with the inner namespace variable named 'FIRST'
           // not conflict with the outer namespace variable named 'FIRST'
  };

  enum class NumOrder {
    SECOND = 2 // conflict with macro `#defien SECOND 2`
               // but won't confict with the global varialbe.
               // not conflict with inner namespace varialbe named 'SECOND'
               // not conflict with outer namespace variable named 'SECOND'
  };

  void fun(Value x) {
    std::cout << "fun called for " << x << "\n";
  }
}

int main(int argc, char** argv)
{
  pingsoli::fun(pingsoli::FIRST);

  std::cout << SECOND << '\n';
  std::cout << static_cast<int>(pingsoli::NumOrder::SECOND) << '\n';

  return 0;
}
