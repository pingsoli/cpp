////////////////////////////////////////////////////////////////////////////////
// from more effective cpp item 1:
// there is no such thing as a null reference.
//
// Differences between pointer and reference
// https://stackoverflow.com/questions/57483/what-are-the-differences-between-a-pointer-variable-and-a-reference-variable-in
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <cassert>

int main(int argc, char *argv[])
{
  {
    // assignment
    {
      // A pointer can be re-assigned
      int x = 5;
      int y = 6;
      int *p;
      p = &x;
      p = &y;
      *p = 10;
      assert(x == 5);
      assert(y == 10);
    }

    {
      // A reference cannot, and must be assigned at initialization.
      int x = 5;
      int y = 6;
      int &r = x; // bind to x
      r = y; // now, x turns to be 6.

      std::cout << "x = " << x << ", reference = " << r << '\n';
    }
  }

  {
    // A pointer has its own memory address and size on stack, whereas a
    // reference share the same memory address takes up some space on the stack.
    int x = 0;
    int &r = x;
    int *p = &x;
    int *p2 = &r;
    assert(p == p2);
  }

  {
    // Pointer can be assigned nullptr directly, whereas reference cannot.
    int *p = nullptr;
    // int &r = nullptr; // error
    int* &r1 = p;
    int &r2 = *p; // no compiling error, but r2 refer to a non-existent int.

    assert(r1 == nullptr);
  }

  {
    // Reference cannot be stuffed into an array, whereas pointers can be.
    // int& ra[] = { 1, 2, 3, 4, 5 }; // error: declaration of `ra` as array of reference
    int* ra[] = { nullptr, nullptr, nullptr }; // ok
  }

  {
    // Const reference can be bound to temporaries, pointers cannot.
    const int &x = int(12);
    // int *y = &int(12); // error
    // const int *y = &int(12); // error
  }

  return 0;
}
