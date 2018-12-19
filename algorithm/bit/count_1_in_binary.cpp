////////////////////////////////////////////////////////////////////////////////
//
// Count '1' in binary
// Count how many '1's in binary representation of a 32-bit integer
//
// Example
// Given 32, return 1.
// Given 5, return 2.
// Given 1023, return 9.
//
// Chanllege
// If the integer is n bits with m bits, can you do it in O(m) time ?
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

// worse solution, need to traverse all bits
// 1000000000000000 will need to traverse all bits
// NOTE: not support negative number
int count_ones_traversal(int num) {
  int count = 0;
  while (num) {
    if ((num & 1) == 1) ++count;
    num = num >> 1;
  }
  return count;
}

// best solution
// support negative number
int count_ones(int num)
{
  int count = 0;
  while (num) {
    num &= num - 1;
    count++;
  }

  return count;
}

int main(int argc, char** argv)
{
  int num;
  while (true) {
    std::cout << "please enter num: ";
    std::cin >> num;

    std::cout << "ones count: " << count_ones(num) << std::endl;
    std::cout << "ones count: " << count_ones_traversal(num) << std::endl;
  }

  return 0;
}
