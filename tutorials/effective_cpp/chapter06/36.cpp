///////////////////////////////////////////////////////////////////////////////
//
// Item 36: Never redefine an inherited non-virtual function.
//
///////////////////////////////////////////////////////////////////////////////
//
// Statically and dynamically bound
//
// Statically bound
// non-virtual functions like B::mf() and D::mf() are statically bound. That
// means that because pB is declared to be of type pointer-to-B, non-virtual
// functions invoked through pB will always be those defined for class B, even
// if pB points to an object of a class derived from B.
//
// Dynamically bound
// virtual functions are dynamically bound, so they don't suffer from this
// problem. If mf were a virtual function, a call to mf through either pB or
// pD would result in an invocation of D::mf(), because what pB and pD really
// point to is an object of type D
//
///////////////////////////////////////////////////////////////////////////////
//
// Things to remember
// Never redefine an inherited non-virtual function.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

class B
{
public:
  void mf()
  {
    std::cout << "B::mf()" << std::endl;
  }
};

class D : public B
{
public:
  void mf()
  {
    std::cout << "D::mf()" << std::endl;
  }
};

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////

  D x;

  B* pB = &x;
  pB->mf();

  D* pD = &x;
  pD->mf();

  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
