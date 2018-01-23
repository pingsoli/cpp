#ifndef __NAMESPACE_TEST_H__
#define __NAMESPACE_TEST_H__

/*
 * Q: What namespace do?
 * A: Sloving the problem of conflict names.
 *
 * Suggestion:
 * 1) Specify namespace name explictly, avoid the automatic lookup.
 *       pingsoli::cos(d);
 *
 * 2) Alias namespace name when it is too long.
 *       namespace CV = CppAnnotation::Virtual;
 *       using namespace CV;
 */

/*
 * // in file1.cc
 * namespace pingsoli
 * {
 *   double cos(double degres)
 *   {
 *     ...
 *   }
 * }
 *
 * // file2.cc
 * namespace pingsoli
 * {
 *   double sin(double degres)
 *   {
 *     ...
 *   }
 * }
 *
 * // In header.h file
 * namespace pingsoli
 * {
 *   double cos(double);
 *   double sin(double);
 * }
 *
 */

namespace pingsoli
{
  enum Value
  {
    FIRST
  };

  void fun(Value x)
  {
    std::cout << "fun called for " << x << "\n";
  }
}

/*
 * // 'Koening lookup'
 * fun(pingsoli::FIRST);
 */

#endif /* __NAMESPACE_TEST_H__ */
