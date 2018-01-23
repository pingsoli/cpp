#include <iostream>
#include <functional>
#include "http_client.h"
#include <cassert>
#include "initializer_list_test.h"
#include "namespace_test.h"
#include "io_manip.h"

/*
 * This is very useful in upgrading.
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

//  initializer_list_test();

//  deprecated_attr_test();

//  const char *buffer = "hello world";
//  char *p = const_cast<char *>(buffer);

//  p[5] = 'z'; /* Won't give the error message, but occur core dumped */

//  std::cout << p << std::endl;

//  int value = 0x12345678;
//
//  std::cout << std::hex
//            << static_cast<int>(
//                 *reinterpret_cast<unsigned char *>(&value)
//                               ) << std::endl;

  rw_file();
  return 0;
}
