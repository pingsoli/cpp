///////////////////////////////////////////////////////////////////////////////
//
// Item 31: Minimize compilation dependencies between files.
//
// pimpl idiom (pointer to implementation)
//
// Things to remember:
// 1) The general idea behind minimizing compilation denpendencies is to depend
// on declarations instead of definitions. Two approaches based on this idea
// are Handle classes and Iterface classes.
//
// 2) Library header files should exists in full and declaration-only forms.
// This applies regardless of whether templates are involved.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "Date.h"
#include "Person.h"

int main(int argc, char** argv)
{
  Date d(2017, 12, 30);
//  std::cout << d.to_string() << std::endl;
//
//  d.setYear(2018);
//  std::cout << d.to_string() << std::endl;

  Person p("hello", d, "lisbon");

  return 0;
}
