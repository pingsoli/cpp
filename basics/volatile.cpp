////////////////////////////////////////////////////////////////////////////////
//
// volatile keyword
// from https://stackoverflow.com/questions/4437527/why-do-we-use-volatile-keyword-in-c
//
// stop compiler from optimizing the code.
//
// options
// set(CMAKE_BUILD_TYPE Debug)
// set(CMAKE_CXX_FLAGS "-fdump-tree-optimized")  # dump gcc optimize code
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

int main(int argc, char** argv)
{
  long count = 0;
  int some_int = 100;

  while (100 == some_int)
  { ++count; }

  return 0;
}
