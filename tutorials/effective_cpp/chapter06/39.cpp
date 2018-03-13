///////////////////////////////////////////////////////////////////////////////
//
// Item 39: Use private inheritance judiciously.
//
// Things to remember
//
// 1) Private inheritance means is-implemented-in-terms of. It's usually
// inferior to composition, but it makes sense when a derived class needs
// access to protected base class members or needs to redefine inherited
// virtual functions.
//
// 2) Unlike composition, private inheritance can enable the empty base
// optimization. This can be important for library developers who strive for
// minimize object sizes.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

///////////////////////////////////////////////////////////////////////////////

class Empty { };

class HoldsAnInt : private Empty
{
private:
  int x;
};

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////

  std::cout << "Empty class size: " << sizeof(Empty) << std::endl;
  std::cout << "HoldsAnInt class size: " << sizeof(HoldsAnInt) << std::endl;
  // Empty class size: 1
  // HoldsAnInt class size: 4

  // Empty Base Optimization (EBO)

  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
