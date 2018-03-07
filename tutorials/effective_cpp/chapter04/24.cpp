///////////////////////////////////////////////////////////////////////////////
//
// Item 24: Declare non-member function when type conversions should apply to
// all parameters
//
// If you need conversions on all parameters to a function(including the one
// that would otherwise be pointed by the this pointer), the function must be
// a non-member.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

class Rational
{
public:
  Rational(int numerator = 0, int denominator = 1)
    : numerator_{numerator}, denominator_{denominator}
  { }

  const Rational operator*(const Rational& rhs)
  {
    return Rational(numerator_ * rhs.numerator_,
                  denominator_ * rhs.denominator_);
  }

  int numerator() const
  { return numerator_; }

  int denominator() const
  { return denominator_; }

private:
  int numerator_, denominator_;
};

void print(const Rational& r)
{
  std::cout << r.numerator() << '/' << r.denominator() << std::endl;
}

const Rational operator*(const Rational& lhs, const Rational& rhs)
{
  return Rational(lhs.numerator() * rhs.numerator(),
                lhs.denominator() * rhs.denominator());
}

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////
  //
  // Make operator* be a member function

  Rational r1(3, 5);
  Rational r2(2, 4);

  Rational r3 = r1 * r2; // ok

  print(r3);

  // mixed-mode arithmetic
//  Rational r4 = r1 * 2; // ok, works fine
//  Rational r5 = 2 * r2; // oops, error
//
//  print(r4);
//  print(r5);

  /////////////////////////////////////////////////////////////////////////////

  Rational r10(10, 10);
  Rational r11(11, 11);

  Rational r12 = r10 * r11; // ok
  Rational r13 = 2 * r10;   // ok
  Rational r14 = r10 * 2;   // ok

  print(r12);
  print(r13);
  print(r14);

  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
