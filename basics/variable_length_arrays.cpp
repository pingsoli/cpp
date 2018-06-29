////////////////////////////////////////////////////////////////////////////////
// VLAs(Variable Length Arrays)
//
// the advantages of VLAs
// 1) VLAs is faster than heap allocation.(VLA is stack allocation).
// 2) make the data close together. (faster)
//
// summary
// Speed is key point. VLAs is created for speed.
////////////////////////////////////////////////////////////////////////////////

void foo(int n) {
  int values[n]; // Declare a variable length array
}

// 3D dimensional arrays
void foo(int x, int y, int z) {
  int values[x][y][z]; // Declare a variable length array
}

int main(int argc, char *argv[])
{
  return 0;
}
