///////////////////////////////////////////////////////////////////////////////
//
// Given a 32-bit signed integer, reverse digits of an integer
//
///////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <iostream>

int reverse(int x)
{
  long long res = 0;

  do {
    res = res * 10 + x % 10;
    x /= 10;
  } while (x);

  return (res<INT_MIN || res>INT_MAX) ? 0 : res;
}

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////
  //
  // Positive number
  {
    int x = 123;
    std::cout << reverse(x) << std::endl;
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  // Negative number
  {
    int x = -123;
    std::cout << reverse(x) << std::endl;
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  // Over max interger
  {
    int x = 2147483648;
    std::cout << reverse(x) << std::endl;
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  // Over min integer
  {
    int x = -2147483648;
    std::cout << reverse(x) << std::endl;
  }

  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
