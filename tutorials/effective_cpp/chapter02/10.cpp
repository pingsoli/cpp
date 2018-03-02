///////////////////////////////////////////////////////////////////////////////
//
// Item 10: Have assignment operators return a reference to *this
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

class Widget
{
public:
  Widget() {}  // default constructor

  Widget(const std::string& name)
    : name_{name}
  { }

  Widget& operator=(const Widget& rhs)
  {
    name_ = rhs.name_;
    return *this;
  }

//  Widget& operators+=(const Widget& rhs)
//  {
//  }
//
//  Widget& operator-=(const Widget& rhs)
//  {
//  }

private:
  std::string name_;
};

int main(int argc, char** argv)
{
  int x, y, z;
  x = y = z = 15;  // chain of assignments
                   // is equal to:
                   // x = (y = (z = 15));
  std::cout << x << ' ' << y << ' ' << z << std::endl;

  Widget w1("window");
  Widget w2, w3;

  w3 = w2 = w1;

  return 0;
}
