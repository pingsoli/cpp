#include <stdio.h>
#include "bar.h"

void bar(int);
void call_c_bar(struct C*, int);

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////
  // calling C++ code from c
  bar(1);
  /////////////////////////////////////////////////////////////////////////////

  return 0;
}