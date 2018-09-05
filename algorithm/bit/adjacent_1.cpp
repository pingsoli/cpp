// example:
// 5 (101) has no adjacent 1.
// 6 (110) has adjacent 1.
//    ^^
//
// solution:
//  101 (5)
// & 10 (5 >> 1)
// ----
//  000 (== 0)
//
//  110 (6)
// & 11 (6 >> 1)
// ----
//  010 (> 0)
//
// result = (n & n >> 1)

#include <iostream>

int main(int argc, char *argv[])
{
  unsigned int num = 0;

  while (true) {
    std::cout << "please enter number: ";
    std::cin >> num;

    if (num == 0) break;

    std::cout << "has adjacent 1: " << ((num & num >> 1) ? "yes" : "no")
      << std::endl;
  }

  return 0;
}
