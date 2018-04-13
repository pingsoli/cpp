#include <iostream>

// load other module variable
extern char a[];
// take care the differences between a[] and *a
// extern char* a; // runtime error

extern void foo(int, double);

int main(int argc, char** argv)
{
  std::cout << a << std::endl;

  foo(1, 0.0);

  return 0;
}
