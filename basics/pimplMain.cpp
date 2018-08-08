#include <iostream>
#include "pimpl.h"

int main(int argc, char *argv[])
{
  Widget w;

  w.setName("hello world");
  std::cout << w.getName() << '\n';

  w.addData({1.9, 2.9, 3.0, 4.1, 5.2});
  w.showData();

  return 0;
}

