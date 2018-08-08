/*
 * how to write a min() and max() macro in c?
 * https://stackoverflow.com/questions/3437404/min-and-max-in-c
 */
#include <stdio.h>

//#defin max(a,b) \
//  ({ __typeof__ (a) _a = (a); \
//     __typeof__ (b) _b = (b); \
//     _a > _b ? _a : _b; })
//
//# min(a,b) \
//  ({ __typeof__ (a) _a = (a); \
//     __typeof__ (b) _b = (b); \
//     _a < _b ? _a : _b; })

/* min() and max() definition in kernel.h */
#define min(x,y) ({                  \
    typeof(x) _min1 = (x);           \
    typeof(y) _min2 = (y);           \
    (void) (&_min1 == &_min2);       \
    _min1 < _min2 ? _min1 : _min2; })

#define max(x,y) ({                  \
    typeof(x) _max1 = (x);           \
    typeof(y) _max2 = (y);           \
    (void) (&_max1 == &_max2);       \
    _max1 > _max2 ? _max1 : _max2; })

/*
 * what does (void) (&_min1 == &_min2) do?
 * type cheching.
 */

int get_zero(void) {
  return 0;
}

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////
  int a = 1, b = 3;
  printf("%d and %d, %d is min!\n", a, b, min(a, b));

  // compound operation
  int c = 2;
  printf("%d + %d and %d, %d is min!\n", a, b, c, min(a + b, c));

  // two compound operations
  int d = 3;
  printf("%d + %d and %d + %d, %d is min!\n", a, b, c, d, min(a + b, c + d));

  // number returned from function
  printf("%d and %d, %d is min!\n", get_zero(), a, min(get_zero(), a));

  // different type, the compiler will give warning, but not failed.
  // and get the wrong result
  int i_v = 1;
  float f_v = 1.2;
  double d_v = 2.5;
  printf("%d and %f, %d is min!\n", i_v, f_v, min(i_v, f_v));
  printf("%d and %f, %d is min!\n", i_v, d_v, min(i_v, d_v));

  return 0;
}
