////////////////////////////////////////////////////////////////////////////////
//
// Calculate the a^n % b where a, b and n are all 32 integers
// from https://www.lintcode.com/en/problem/fast-power/
//
// Example
// For 2^31 % 3 = 2
// For 100^1000 = 0
//
// Solution
// formula
// (a * b) % p = ((a % p) * (b % p)) % p
//
// so, we can do like the following.
// a^n = a^n/2 * a^n/2 = a^n/4 * a^n/4 * a^n/4 * a^n/4 = ....
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

int fast_power(int a, int b, int n)
{
  if (1 == n)      return a % b;
  else if (0 == n) return 1 % b;
  else if (0 > n)  return -1;

  long long product = fast_power(a, b, n / 2);
  product = (product * product) % b;
  if (1 == n % 2)
    product = (product * a) % b;

  return product;
}

int main(int argc, char** argv)
{
  int a   = 2;
  int b   = 3;
  int n   = 31;
  int mod = -1;

  mod = fast_power(a, b, n);

  std::cout << a << "^" << n << " % " << b << " = " << mod << std::endl;
  return 0;
}
