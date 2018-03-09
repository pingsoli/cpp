///////////////////////////////////////////////////////////////////////////////
//
// Item 30: Understand the ins and outs of inlining.
//
// The idea behind a inline function is to replace each call of that function
// with its code body.
//
// faster, but bloats the code
// increase the size of object code (code bloat), may lead to addtional paging,
// and reduce the instruction cache hit rate.
//
// Inlining in most C++ programs is a compile-time activity.
//
// Library designer must evaluate the impact of declaring functions inline,
// because it's impossible to provide binary upgrades to the client-visible
// inline functions in a library. In other words, if 'f' is an inline function
// in a library, clients of the library compile the body of 'f' into their
// applications. If a library implementer later decides to change f, the
// clients who've used 'f' must recompile.
//
// Things to remember:
// 1) Limit most inlining to samll, frequently called functions. This
// facilitates debugging and binary upgradability, minimizes potential code
// bloat, and maximizes the chances of greater of greater program speed.
//
// 2) Dont't declare function templates inline just because they appear in
// header files.
//
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  return 0;
}
