#include <iostream>
#include <functional>
#include <cassert>

/*
 * This is very useful in upgrading program.
 * No matter the function is invloked or not,
 * compiler will give the warning with deprecated attribute.
 */
[[deprecated]] void deprecated_attr_test()
{
}

void f(const int* p1, int* p2)
{
  int i = *p1;
  *p2 = 7;
  int j = *p1;

  if (i != j) {
    std::cout << "*p1 changed, but it don't change via pointer p1!\n";
    assert(p1 == p2);
  }
}

int main(int argc, char **argv)
{
//  int x = 5;
//  f(&x, &x);

//  deprecated_attr_test();

// big-endian or little-endian checking
//
//  int value = 0x12345678;
//
//  std::cout << std::hex
//            << static_cast<int>(
//                 *reinterpret_cast<unsigned char *>(&value)
//                               ) << std::endl;

  return 0;
}
