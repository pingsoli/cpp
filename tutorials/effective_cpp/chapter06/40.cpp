///////////////////////////////////////////////////////////////////////////////
//
// Item 40: Use multiple inheritance judiciously.
//
// Things to remember
//
// 1) Multiple inheritance is more complex than single inheritance. It can lead
// to new ambiguity issues and to the need for virtual inheritance.
//
// 2) Virtual inheritance imposes costs in size, speed, and complexity of
// initialization and assignment. It's most pratical when virtual base classes
// have no idea.
//
// 3) Multiple inheritance does have legitimate uses. One scenario involves
// combining public inheritance from an interface class with private
// inheritance from a class that helps with implementation.
//
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  return 0;
}
