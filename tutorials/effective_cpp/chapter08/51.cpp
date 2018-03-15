///////////////////////////////////////////////////////////////////////////////
//
// Item 51: Adhere to convention when writing new and delete.
//
// Things to remember
//
// 1) operator new should contain a infinite loop trying to allocate memory,
// should call the new-handler if it can't satisfy a memory request, and should
// handle requests for zero bytes, class-specific versions should handle
// requests for larger blocks than expected.
//
// 2) operator delete should do nothing if passed a pointer that is null,
// Class-specific versions should handle blocks that are larger than expected.
//
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  return 0;
}
