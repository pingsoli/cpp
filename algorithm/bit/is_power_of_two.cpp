// 4 is power of 2, 100 & 011 = 0
// 5 is not power of 2, 101 & 100 = 100 (4)
// 8 is power of 2, 1000 & 0111 = 0
// 9 is not power of 2, 1001 & 1000 = 1000 (8)
//
// formula:
// num & (num - 1) == 0

#include <iostream>

bool isPowerOfTwo(ulong num) {
  return (num != 0) && ((num & (num - 1)) == 0);
}

int main(int argc, char *argv[])
{
  int num = 8;

  std::cout << "num " << num << (isPowerOfTwo(num) ? " is" : " is not")
    << " power of two" << '\n';

  return 0;
}
