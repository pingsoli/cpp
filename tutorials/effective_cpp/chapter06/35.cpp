///////////////////////////////////////////////////////////////////////////////
//
// Item 35: Consider alternatives to virtual functions.
//
///////////////////////////////////////////////////////////////////////////////
//
// Summary
//
// 1) Use the non-virtual interface idiom (NVI idiom), a form of the Template
// Method design pattern that wraps public non-virtual member functions around
// less accessible virtual functions.
//
// 2) Replace virtual functions with functions pointer data members, a
// stripped-down manifestation of the Strategy design pattern.
//
// 3) Replace virtual functions with tr1::function data members, thus allowing
// use of any callable entity with a signature compatible with what you need.
// This, too, is a form of the Strategy design pattern.
//
// 4) Replace virtual functions in one hierarchy with virtual functions in
// another hierarchy. This is the conventional implementation of the Strategy
// design pattern.
//
///////////////////////////////////////////////////////////////////////////////
//
// Things to remember
//
// 1) Alternatives to virtual functions include the NVI idiom and various
// forms of the Strategy design pattern. The NVI idiom is itself an example
// of the Template Method design pattern.
//
// 2) A disadvantage of moving functionality from a member function to a
// function outside the class is that non-member function lacks access to the
// class's non-public members.
//
// 3) tr1::function objects act like generalized function pointers. Such
// objects support all callable entities compatible with a given target
// signature.
//
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  return 0;
}
