////////////////////////////////////////////////////////////////////////////////
//
// Data Structure Alignment
//
// Why need data structure alignment ?
// Effciency.
//
// the rule of data alignment ?
// Choose the largest primitive data type as alignment.
//
// References
// [1] https://en.wikipedia.org/wiki/Data_structure_alignment
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

////////////////////////////////////////////////////////////////////////////////
struct MyData {
  short data1;  // 2 bytes
  short data2;  // 2 bytes
  short data3;  // 2 bytes
                // total: 6 bytes
};
////////////////////////////////////////////////////////////////////////////////

// force specific size to align

// alignment according to largest type
struct MixedData {
  short data1;  // 2 bytes
  short data2;  // 2 bytes
  int   data3;  // 4 bytes
  short data4;  // 4 bytes
};

#pragma pack(push)  // push current alignment to stack
#pragma pack(2)     // set alignment to 2 bytes alignment

struct MixedDataWithPack {
  short data1;  // 2 bytes
  short data2;  // 2 bytes
  int   data3;  // 4 bytes
  short data4;  // 2 bytes
};

#pragma pack(pop)   // restore original alignment from stack
////////////////////////////////////////////////////////////////////////////////

struct MixedDataAutoAlign {
  char  data1;  // 2
  short data2;  // 2
  int   data3;  // 4
  char  data4;  // 4
};

// the above code will be padded with a proper alignment, like the following

struct MixedDataPaddingByCompiler {
  char  data1;        // 1 byte
  char  padding[1];   // 1 byte for the following 'short'
  short data2;        // 2 bytes
  int   data3;        // 4 bytes
  char  data4;        // 1 byte
  char  padding2[3];  // 3 bytes to make total size of the structure 12 bytes
};
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  std::cout << "struct MyData size: " << sizeof(MyData) << std::endl;

  std::cout << "struct MixedData size: " << sizeof(MixedData) << std::endl;

  std::cout << "struct MixedDataWithPack size: "
    << sizeof(MixedDataWithPack) << std::endl;

  std::cout << "struct MixedDataPaddingByCompiler size: "
    << sizeof(MixedDataPaddingByCompiler) << std::endl;

  std::cout << "structure MixedDataAutoAlign size: "
    << sizeof(MixedDataAutoAlign) << std::endl;

  return 0;
}
