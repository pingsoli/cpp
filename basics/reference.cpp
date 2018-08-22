////////////////////////////////////////////////////////////////////////////////
// from more effective cpp item 1:
// there is no such thing as a null reference.
//
// the comparison between pointers and references.
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <memory>
#include <vector>

int main(int argc, char *argv[])
{
  {
    // char *p = 0; // p is a null pointer.
    // char& pr = *p; // make reference refer to deferenced null pointer.

    // std::cout << *p << '\n'; // it's illegal.
    // std::cout << pr << '\n'; // error, SIGSEV
  }

  return 0;
}
