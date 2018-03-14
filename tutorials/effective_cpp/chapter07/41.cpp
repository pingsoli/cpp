///////////////////////////////////////////////////////////////////////////////
//
// Item 41: Understand implicit interfaces and compile-time polymorphism.
//
///////////////////////////////////////////////////////////////////////////////
//
// Things to remember
//
// 1) Both classes and templates support interfaces and polymorphism.
//
// 2) For classes, interfaces are explicit and centered on function signatures.
// Polymorphism occurs at runtime through virtual functions.
//
// 3) For template parameters, interfaces are implicit and based on valid
// expressions. Polymorphism occurs during compilation through template
// instantiation and function overloading resolution.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <utility>

class Widget
{
public:
  Widget() = default;
  virtual ~Widget() {}

  virtual std::size_t size() const {
    return size_;
  }

  virtual void normalize() {
    std::cout << "normalize" << std::endl;
  }

  void swap(Widget& other) {
    if (&other == this) return;
    std::swap(*this, other);
  }

private:
  std::size_t size_;
};

template <typename T>
void do_processing(T& w)
{
  if (w.size() >= 10)
  {
    std::cout << "size is bigger than 10" << std::endl;
  }
  else
  {
    std::cout << "size is smaller than 10" << std::endl;
  }
}

int main(int argc, char** argv)
{
  Widget w;
  do_processing<Widget>(w);

  return 0;
}
