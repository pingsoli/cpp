///////////////////////////////////////////////////////////////////////////////
//
// Return Value Optimization(RVO)
// Copy elision and move
//
// Copy elision is a compiler optimization technique that eliminates
// unnecessary copying/moving of objects.
//
// Reference
// https://www.ibm.com/developerworks/community/blogs/5894415f-be62-4bc0-81c5-3956e82276f3/entry/RVO_V_S_std_move?lang=en
// https://en.wikipedia.org/wiki/Copy_elision#Return_value_optimization
//
// NOTE
// Default, RVO is enabled in g++. But if you use "-fno-elide-constructors"
// the g++ compiler will not optimize constructor.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

///////////////////////////////////////////////////////////////////////////////

struct BigObject
{
public:
  BigObject() {
    std::cout << "default constructor" << std::endl;
  }

  BigObject(const BigObject&) {
    std::cout << "copy constructor" << std::endl;
  }

  ~BigObject() {
    std::cout << "destructor" << std::endl;
  }
};

BigObject foo() {
  BigObject local_object;
  return local_object;
}

BigObject bar(int n) {
  BigObject local_obj, another_local_obj;

  if (n > 2) {
    return local_obj;
  } else {
    return another_local_obj;
  }
}

BigObject return_big_object(int n)
{
  int p = 0;
  std::string s("hello");

  // do something

  return BigObject();
}

///////////////////////////////////////////////////////////////////////////////

struct C
{
  C() { std::cout << "default constructor\n"; }
  C(const C&) { std::cout << "copy constructor\n"; }
  ~C() { std::cout << "destructor\n"; }
};

void f() {
  C c;
  throw c;
}

C a_class_c_instance() {
  return C();
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////

//  BigObject named_rvo = return_big_object(0);
//  BigObject rvo = foo();

  /////////////////////////////////////////////////////////////////////////////

//  BigObject without_rvo = bar(1);

  /////////////////////////////////////////////////////////////////////////////

//  try {
//    f();
//  } catch (C c)
//  {}
//  // twice "Hello world"

  C c = a_class_c_instance();

  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
