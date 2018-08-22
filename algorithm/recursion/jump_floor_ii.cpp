////////////////////////////////////////////////////////////////////////////////
// 题目：一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶，，，它也可以跳上
// n级，求该青蛙跳上n级台阶总共有多少种方法?
//
// solution:
// 1 floor:  f(1) = 1
// 2 floors: f(2) = f(1) + 1 = 2
// 3 floors: f(3) = f(2) + f(1) + 1 = 4
// 4 floors: f(4) = f(3) + (f2) + f(1) + 1 = 8
//
// f(n) = f(n - 1) + f(n - 2) + ... + f(2) + f(1) + 1
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

// recursion solution
// unsigned long long jump_floor(int n) {
//   if (n <= 0) return 0;
//   if (n == 1 || n == 2) return n;
//
//   return 2 * jump_floor(n - 1);
// }

// iterate soution
unsigned long long jump_floor(int n) {
  unsigned long long Counter[101] = { 0 };

  Counter[1] = 1;
  Counter[2] = 2;

  int index = 2; // index starts from 2.
  if (n <= 2) return Counter[n];

  // avoid overflow, max n is 100.
  if (n > 100) n = 100;

  for (int i = index + 1; i <= n; ++i)
    Counter[i] = 2 * Counter[i - 1];

  return Counter[n];
}

int main(int argc, char *argv[])
{
  int n = 0;
  do {
    std::cout << "please enter n(n < 0 to quit): ";
    std::cin >> n;
    std::cout << jump_floor(n) << '\n';
  } while (n > 0);

  return 0;
}
