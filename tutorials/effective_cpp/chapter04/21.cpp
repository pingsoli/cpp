///////////////////////////////////////////////////////////////////////////////
//
// Item 21: Don't try to return a reference when you must return an object
//
// Never return a pointer or reference to a local stack object, a reference
// to a heap-allocated object, or a pointer or reference to local static object
// if there is a chance that more than one such object will be needed, (Item 4
// provides an example of a design where returning a reference to a local
// static is reasonable, at least in single-threaded environments)
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

class Rational
{
public:
  Rational(int numerator, int denominator)
    : n{numerator}, d{denominator}
  {}

  void print()
  {
    std::cout << d << '/' << n << '\n';
  }

private:
  int n, d;
  friend const Rational operator*(const Rational& lhs, const Rational& rhs);
};

// why return type is const ?
const Rational operator*(const Rational& lhs, const Rational& rhs)
{
  return Rational(lhs.n * rhs.n, lhs.d * rhs.d);
}

int main(int argc, char** argv)
{
  Rational r1(3, 5);
  Rational r2(4, 2);
  Rational r3 = r1 * r2;
  Rational r4 = r1 * r2 * r3;

  r3.print();
  r4.print();

  return 0;
}
