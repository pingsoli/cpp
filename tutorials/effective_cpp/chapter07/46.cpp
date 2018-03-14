///////////////////////////////////////////////////////////////////////////////
//
// Item 46: Define non-member functions inside templates when type conversion
// are desired.
//
// Things to remember
//
// When writing a class template that offers function related to the template
// that support implicit type conversions on all parameters. define those
// functions as friend inside the class template.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

template <typename T>
class Rational;

template <typename T>
const Rational<T> doMultiply(const Rational<T>& lhs,
                             const Rational<T>& rhs);

template <typename T>
class Rational
{
public:
  Rational(const T& numerator = 0,
           const T& denominator = 1)
    : numerator_{numerator},
      denominator_{denominator}
  {}

  const T numerator() const { return numerator_; }
  const T denominator() const { return denominator_; }

private:
  T numerator_, denominator_;

//  // the function is inline, and has only one line code.
//  // but if the function has many lines, we may need to move out the function
//  friend const Rational operator*(const Rational& lhs, const Rational& rhs)
//  {
//    return Rational(lhs.numerator() * rhs.numerator(),
//                  lhs.denominator() * rhs.denominator());
//  }

  friend const Rational<T> operator*(const Rational<T>& lhs,
                                     const Rational<T>& rhs)
  {
    return doMultiply(lhs, rhs);
  }
};

template <typename T>
const Rational<T> doMultiply(const Rational<T>& lhs, const Rational<T>& rhs)
{
  return Rational<T>(lhs.numerator() * rhs.numerator(),
                   lhs.denominator() * rhs.denominator());
}

template <typename T>
void print(const Rational<T>& r)
{
  std::cout << r.numerator() << '/' << r.denominator() << std::endl;
}

int main(int argc, char** argv)
{
  Rational<int> r1(2, 3);
  Rational<int> r2(4, 5);

  Rational<int> r3 = r1 * r2;
  Rational<int> r4 = r1 * 2;
  Rational<int> r5 = 2 * r1;

  print(r3);
  print(r4);
  print(r5);

  return 0;
}
