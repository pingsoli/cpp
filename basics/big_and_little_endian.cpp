///////////////////////////////////////////////////////////////////////////////
//
// Big-Endian and Little-Endian
//
// 0x12345678
//
//    12       34       56      78
// 00010010 00110100 01010110 01111000
//
//
// Big-Endian
//
// address increase
// ---------------------------------->
// 00010010 00110100 01010110 01111000
//
//
// Little-Endian
// address increase
// ---------------------------------->
// 01111000 01010110 00110100 00010010
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

int main(int argc, char** argv)
{
  // big-endian or little-endian checking

  int value = 0x12345678;

  // ouput 78 is big-endian, 12 is little-endian
  std::cout << std::hex <<
            static_cast<int>
            (
              *reinterpret_cast<unsigned char *>(&value)
            )
            << std::endl;

  return 0;
}
