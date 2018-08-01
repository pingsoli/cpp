// auto keyword

int main(int argc, char *argv[])
{
  int x1; // potentially unintialized.
  // auto x2; // error! initializer required.
  auto x3 = 0; // fine. x's value is well-defined.

  return 0;
}
