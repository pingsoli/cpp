#include <stdio.h>
#include <stdlib.h>

void not_free_memory(void) {
  int *x = (int *) malloc(10 * sizeof(int)); // problem 1: heap block overrun
  x[10] = 0;                            // problem 2: memory leak -- x not freed
}

int main(int argc, char *argv[])
{
  not_free_memory();

  return 0;
}
