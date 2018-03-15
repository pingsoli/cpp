///////////////////////////////////////////////////////////////////////////////
//
// Item 52: Write placement delete if you write placement new.
//
// Things to remember
//
// 1) When you write a placement version of operator new, be sure to write the
// corresponding placement version of operator delete. If you don't, your
// program may experience subtle, intermittent memory leaks.
//
// 2) When you declare placement versions of new and delete, be sure not to
// unintentionally hide the normal versions of those functions.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// the difference between operator new and placement new ?
// when an operator new function takes extra parameters, that function is known
// as a placement version of new.
//
// class Widget
// {
// public:
//   static void* operator new(std::size_t size, std::ostream& logStream)
//     throw(std::bad_alloc);
//
//   static void operator delete(void* pMemory) throw();
//   static void operator delete(void* pMemory, std::ostream& logStream) throw();
// };
//
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  return 0;
}
