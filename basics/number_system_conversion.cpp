////////////////////////////////////////////////////////////////////////////////
//
// Number system conversion
//
// bin -> decimal
// hex -> decimal
// oct -> decimal
//
////////////////////////////////////////////////////////////////////////////////

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

std::string long_to_hex(long num, char padding, int width) {
  std::ostringstream oss;
  oss << std::setfill(padding) << std::setw(width) << std::hex << num;
  return oss.str();
}

long hex_to_long(const std::string &str) {
  long num;
  std::istringstream iss(str);
  iss >> std::hex >> num;
  return num;
}

int main(int argc, char** argv)
{
  long num = 100;
  char padding = '0';
  int width = 16;

  std::string str(long_to_hex(num, padding, width));

  std::cout << str << std::endl;
  std::cout << "decimal number: " << hex_to_long(str) << '\n';

  return 0;
}
