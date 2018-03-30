///////////////////////////////////////////////////////////////////////////////
//
// const keyword
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>

void f(const int* p1, int* p2)
{
  int i = *p1;
  *p2 = 7;
  int j = *p1;

  if (i != j) {
    std::cout << "*p1 changed, but it don't change via pointer p1!\n";
  }

  assert(p1 == p2);
  std::cout << "p1 = " << *p1 << "; p2 = " << *p2 << std::endl;
}

int main(int argc, char **argv)
{
  int x = 5;
  f(&x, &x);

  return 0;
}
