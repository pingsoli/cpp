///////////////////////////////////////////////////////////////////////////////
//
// Item 11: Handle assignment to self in operator=.
//
// 1) Make sure operator= is well-behaved when an object is assigned to itself.
// Techniques include comparing address of source and target objects, careful
// statement ordering, and copy-and-swap.
//
// 2) Make sure that any function operating on more than one object behaves
// correctly if two or more of the objects are the same.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

class BitMap
{
public:
  BitMap(const std::string& name)
    : name_{name}
  {}

  std::string name() const {
    return name_;
  }

private:
  std::string name_;
};

class Widget
{
public:
  Widget()
    : pb{new BitMap("bitmap")}
  {}

  Widget& operator=(const Widget& rhs)
  {

// What's the problem in following code ?
//    delete pb;
//    pb = new BitMap(*rhs.pb);
//    return *this;

    ///////////////////////////////////////////////////////////////////////////
    //
    // identity test
    if (this == &rhs) return *this;

    delete pb;
    pb = new BitMap(*rhs.pb);
    return *this;
  }

  void print()
  {
    std::cout
      << "bitmap name: " << pb->name() << '\n';
  }

private:
  BitMap* pb;
};

int main(int argc, char** argv)
{
  Widget w1, w2(w1);

  w1 = w1;  // what will happen ?
  w1.print();

  return 0;
}
