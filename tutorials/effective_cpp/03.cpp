// Item 3: Use const whenever possible
// 1) Declaring something const help compilers detect useage errors.
// 2) Compilers enforce bitwise constness, but you should program
//    using logical constness.
// 3) When const and non-const member functions have esstially identical
//    implementation, code duplication can be avoid by having the
//    non-const version call the const version.

#include <iostream>
#include <vector>
#include "text_block.h"

// const -> a object should not be modified

char greeting[] = "hello";
char *p = greeting;  // non-const pointer
                     // non-const data

const char *q = greeting;  // non-const pointer
                           // const data

char * const r = greeting;  // const pointer
                            // non-const data

const char *const o = greeting;  // const pinter
                                 // const data

/*
 * the following function take the same parameter type.
 * there is no difference.
 *
 * void f1(const Widget *pw)
 * void f2(Widget const* pw)
 */

void traverse_vec(std::vector<int>& v)
{
  for (auto& e: v)
    std::cout << e << std::endl;
}

class Rational
{
private:
  int num_, den_;

public:
  Rational(int num = 1, int den = 1) :
    num_{num}, den_{den}
  {
  }

  friend const Rational operator*(const Rational& lhs, const Rational& rhs);
};

// Think off it, why need const constriant?
// if remove 'const', (a * b) = c; is fine.
// Rational operator*(const Rational& lhs, const Rational& rhs);
const Rational operator*(const Rational& lhs, const Rational& rhs)
{
  return Rational(lhs.num_ * rhs.num_, lhs.den_ * rhs.den_);
}

int main(int argc, char **argv)
{
  std::vector<int> vec({1, 2, 3, 4, 5, 6});

  {
    traverse_vec(vec);
    // Output:
    // 1 2 3 4 5 6 
  }

  {
    const std::vector<int>::iterator iter = vec.begin();
    *iter = 10;  // Ok, changes the what iter points to
    //  ++iter;  // error, iter is const

    traverse_vec(vec);
    // Output:
    // 10 2 3 4 5 6 
  }

  {
    std::vector<int>::const_iterator citer = vec.cbegin();
    // *citer = 10; // error, *citer is const, read-only
    ++citer;     // fine, change citer
  }

  {
    Rational a, b, c;

    // (a * b) = c;  // If const constraint
    // if (a * b = c)  // is equial to bool operator*(const Rational& lhs, const Rational& rhs);
    //   std::cout << "a * b = c" << std::endl;
  }

  TextBlock tb("hello");
  std::cout << tb[0] << std::endl;
  tb[0] = 'x';  // fine -- writing a non-cosnt TextBlock
  tb.print();

  const TextBlock ctb("world");
  std::cout << ctb[0] << std::endl;
  // ctb[0] = 't';  // error! -- writing a const TextBlock

//  CTextBlock cctb("hello");
//  char *pc = &cctb[0];
//  cctb.print();  // hello
//
//  *pc = 'J';
//  cctb.print();  // Jello

  return 0;
}
