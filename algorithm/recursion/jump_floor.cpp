////////////////////////////////////////////////////////////////////////////////
// Suppose a fog can jump one step or two steps every time.
// now, stair has N steps, how many ways to jump to N steps ?
//
// solution:
// f(n) = f(n-1) + f(n-2)
//
// N steps can jump one(n-1) or two steps(n-2), so f(n) equals f(n-1) + f(n-2)
////////////////////////////////////////////////////////////////////////////////
#include <iostream>

// recursion solution
// long long jump_floor(int n) {
//   if (n <= 0) return -1;
//   if (n == 1 || n == 2) return n;
//
//   return jump_floor(n-1) + jump_floor(n-2);
// }

// iterator solution
unsigned long long jump_floor(int n) {
  unsigned long long Counter[101] = { 0 };
  Counter[1] = 1;
  Counter[2] = 2;

  int calculatedIndex = 2;

  if (n <= calculatedIndex)
    return Counter[n];

  if (n > 100)
    n = 100;

  for (int i = calculatedIndex + 1; i <= n; ++i)
  {
    Counter[i] = Counter[i - 1] + Counter[i - 2];
  }

  return Counter[n];
}


int main(int argc, char *argv[])
{
  int n = 0;

  do {
    std::cout << "please enter n (n < 0 to quit): ";
    std::cin >> n;
    std::cout << jump_floor(n) << '\n';
  } while (n > 0);

  return 0;
}
