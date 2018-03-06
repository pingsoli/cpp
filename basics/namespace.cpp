/*
 * ======================================================================
 *
 * FAQ:
 * Q: What namespace do?
 * A: Sloving the problem of conflict names.
 *
 * Tips:
 * 1) Specify namespace name explictly, avoid the automatic lookup.
 *       pingsoli::cos(d);
 *
 * 2) Alias namespace name when it is too long.
 *       namespace CV = CppAnnotation::Virtual;
 *       using namespace CV;
 *
 * ======================================================================
 *
 * Example:
 * // file1.cpp
 * namespace pingsoli {
 *   double cos(double degres) {
 *     ...
 *   }
 * }
 *
 * // file2.cpp
 * namespace pingsoli {
 *   double sin(double degres) {
 *     ...
 *   }
 * }
 *
 * // header.h
 * namespace pingsoli
 * {
 *   double cos(double);
 *   double sin(double);
 * }
 *
 * ======================================================================
 *
 * namespace lookup
 *
 * // 'Koening lookup'
 * fun(pingsoli::FIRST);
 *
 * pingsoli::fun(pingsoli::FIRST)
 *
 * ======================================================================
 */

#include <iostream>

// #define FIRST 10

namespace pingsoli
{
  enum Value
  {
    FIRST  // conflict with macro `#define FIRST 10`
  };

  void fun(Value x)
  {
    std::cout << "fun called for " << x << "\n";
  }
}

int main(int argc, char** argv)
{
  pingsoli::fun(pingsoli::FIRST);

  return 0;
}
