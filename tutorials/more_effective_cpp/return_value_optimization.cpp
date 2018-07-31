#include <iostream>

class Rational
{
public:
  Rational(int num = 0, int den = 1)
    : numerator_(num), denominator_(den)
  {}

  int numerator() const { return numerator_; }
  int denominator() const { return denominator_; }

private:
  int numerator_;
  int denominator_;
};

const Rational operator+(const Rational& lhs, const Rational& rhs)
{
  // return value optimization.
  return Rational(lhs.numerator() + rhs.numerator(),
                  lhs.denominator() + rhs.denominator());
}

const Rational operator*(const Rational& lhs, const Rational& rhs)
{
  return Rational(lhs.numerator() * rhs.numerator(),
                  lhs.denominator() * rhs.denominator());
}

std::ostream& operator<<(std::ostream& os, const Rational& r)
{
  return (os << r.numerator() << " / " << r.denominator());
}

int main(int argc, char *argv[])
{
  Rational r1(1, 2);
  Rational r2(2, 3);
  Rational r3 = r1 + r2;
  r3 = r1 * r2;

  std::cout << r3 << '\n';
  return 0;
}
