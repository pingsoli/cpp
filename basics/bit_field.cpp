////////////////////////////////////////////////////////////////////////////////
// what does bit field used for ?
// save space. regular c++ data type may a little big.
// we want more little space (such as use one c++ basic data type to store
// multiple kinds of value). that cause bit field.
//
// how much space does bit field use ?
// see below.
//
// use case:
// as flags.
//
// Bit field is portable ?
// yes, it's portable.
////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <iostream>

// total space is 1 byte
struct {
  uint8_t is_keyword : 1;
  uint8_t is_extern  : 1;
  uint8_t is_static  : 1;
} flags;


// the old fashion way to do this
#define IS_KEYWORD 0x01
#define IS_EXTERN  0x02
#define IS_STATIC  0x04

uint8_t old_flags;


int main(int argc, char *argv[])
{
  std::cout << sizeof(flags) << '\n'; // 1 bytes, we only use 3 bit

  flags.is_static  = 1;
  flags.is_extern  = 0;
  flags.is_keyword = 0;

  if (flags.is_static) {
    // ...
  }


  old_flags = 4;

  if (old_flags & IS_STATIC) {
    // ...
  }

  return 0;
}
