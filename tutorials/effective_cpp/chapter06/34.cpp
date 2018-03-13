///////////////////////////////////////////////////////////////////////////////
//
// Item 34: Differentiate between inheritance of interface and inheritance
// of implementation.
//
///////////////////////////////////////////////////////////////////////////////
//
// Pure virtual, inpure virtual and non-virtual ?
//
// The purpose of declaring a pure function is to have derived classes inherit
// a function interface only.
//
// The purpose of declaring a simple virtual function is to have derived
// classes inherit a function interface as well as a default implementation.
//
// The purpose of declaring a non-virtual function is to have derived classes
// inherit a function interface as well as mandatory implementation.
//
///////////////////////////////////////////////////////////////////////////////
//
// Things to remember:
//
// 1) Inheritance of interface is different from inheritance of implementation.
// Under public inheritance, derived classes always inherit base classes
// interfaces.
//
// 2) Pure virtual functions specify inheritance of interface only.
//
// 3) Simple (impure) virtual functions specify inheritance of interface plus
// inheritance of a default implementation.
//
// 4) Non-virtual functions specify inheritance of interface plus inheritance
// of a mandatory implementation.
//
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  return 0;
}
