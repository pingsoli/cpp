////////////////////////////////////////////////////////////////////////////////
// stringstream is based on readbuf, not support move semantics by now.
////////////////////////////////////////////////////////////////////////////////
#include <sstream>
#include <iostream>

int main(int argc, char *argv[])
{
  int n;
  std::istringstream in;  // could also use in ("1 2")
  in.str("1 2");
  in >> n;
  std::cout << "after reading the first int from \"1 2\", the int is "
            << n << ", str() = '" << in.str() << "'" << std::endl;

  std::ostringstream out("1 2");
  out << 3;
  std::cout << "after writing the int '3' to output stream \"1 2\""
            << ", str() = '"<< out.str() << "'" << std::endl;

  std::ostringstream ate("1 2", std::ios_base::ate);
  ate << 3;
  std::cout << "after writing the int '3' to append stream \"1 2\""
            << ", str() = '" << ate.str() << "'" << std::endl;

  // the out would like this:
  // after reading the first int from "1 2", the int is 1, str() = '1 2'
  // after writing the int '3' to output stream "1 2", str() = '3 2'
  // after writing the int '3' to append stream "1 2", str() = '1 23'

  return 0;
}
