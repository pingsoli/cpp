///////////////////////////////////////////////////////////////////////////////
//
// Item 16: Use the same form in corresponding uses of new and delete.
//
// delete Vs. delete []
//
// 1) If you use [] in a new expression, you must use [] in the corresponding
// delete expression. If you don't use [] in a new expression, you mustn't use
// [] in the corresponding delete expression.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
  std::string* str_arr = new std::string[4];

  // delete str_arr;  // error, what will happen ?
  // terminated by signal SIGSEGV (Address boundary error)

  delete [] str_arr;  // ok

  // what does the `delete []` do ?
  // how to know the boundary of the array ?
  //
  // the memory for an array usually includes the size of an array, thus make
  // it easy for delete to know how many destructors to call.

  return 0;
}
