///////////////////////////////////////////////////////////////////////////////
//
// Item 17: Store newed objects in smart pointers in standalone statements.
//
// Store newed objects in a smart pointers in standalone statements. Failure to
// do this can lead to subtle resource leaks when execeptions are thrown.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <memory>

class Widget
{
public:
  Widget(int width, int height)
    : width_{width}, height_{height}
  {}

private:
  int width_, height_;
};

void processWidget(std::shared_ptr<Widget> pw, int priority)
{
  std::cout << "processWidget test" << std::endl;
}

int priority()
{
  // do something
  return 20;
}

int main(int argc, char** argv)
{
  processWidget(std::shared_ptr<Widget>(new Widget(10, 10)), priority());

  // the compiler must generate code to do these three things
  // 1. Call priority
  // 2. Execute 'new Widget'
  // 3. Call std::shared_ptr constructor

  // what is the sequnce of the execution ?
  // consider this situation
  //
  // 1. Execute 'new Widget'
  // 2. Call priority
  // 3. Call std::shared_ptr constructor
  //
  // and priority function yields a exeception, the pointer returned from
  // 'new Widget' will be lost.

  std::shared_ptr<Widget> pw(new Widget(10, 10));
  processWidget(pw, priority());

  return 0;
}
