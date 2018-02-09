/*
 * Difference between new keyword and operator new ?
 * Operator new is a function that allocates raw memory. (only for PODs)
 * New keyword is what you normally use to create an object from the free store.
 *
 * refers to: https://stackoverflow.com/questions/1885849/difference-between-new-operator-and-operator-new
 */
#include <iostream>
#include <vector>

class Base
{
public:
  void* operator new(size_t sz)
  {
    std::cerr << "new " << sz << " bytes\n";

    // double-colon is to avoid infinite recursion
    return ::operator new(sz);
  }

  void operator delete(void* p)
  {
    std::cerr << "delete\n";
    ::operator delete(p);
  }

private:
  int m_data;
};

class Derived : public Base
{
private:
  // 4 bytes
  int m_derived_data;

  // 24 bytes per object, 24 * 4 = 96 bytes
  std::vector<int> x, y, z, w;
};

int main(int argc, char** argv)
{
  // Basic usage
  char* x = static_cast<char *>(operator new(100));

  Base* b = new Base;
  delete b;

  Derived* d = new Derived;
  delete d;

  // output:
  // new 4 bytes
  // delete
  // new 104 bytes
  // delete

  return 0;
}
