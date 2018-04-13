#include <stdio.h>
#include "foo.h"

void foo(int i) {
  printf("void f(int i)\n");
}

int g(double d) {
  printf("int g(double d)\n");
  return 0;
}

double h() {
  printf("double h()\n");
  return 0.0;
}
