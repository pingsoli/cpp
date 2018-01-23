#include <iostream>
#include "utility.h"

int main(int argc, char **argv)
{
  std::string s("0xfffffffffff");

  try {
    std::cout << HexToInt(s) << std::endl;
  } catch(std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
