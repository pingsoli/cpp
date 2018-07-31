////////////////////////////////////////////////////////////////////////////////
// how to make a class noncopyable ?
// you can refer to boost::noncopyable.
// the following code is our way to achive this.
//
// more detail can see: emtpy base optimization.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

struct noncopyable {
  noncopyable() {};
  noncopyable(const noncopyable&) = delete;
  noncopyable& operator=(const noncopyable&) = delete;
};

class MyClass : private noncopyable {
public:
  MyClass(int id) : id_(id) {}
  int getId() const { return id_; }

private:
  int id_;
};

int main(int argc, char *argv[])
{
  std::cout << sizeof(MyClass) << '\n'; // 4 bytes

  std::cout << "noncopyable class size: "
            << sizeof(noncopyable) << '\n'; // 1 bytes, empty base optimization.

  MyClass cls1(2);
  // MyClass cls2(std::move(cls1)); // illegal
  // MyClass cls3 = cls1; // illegal

  return 0;
}
