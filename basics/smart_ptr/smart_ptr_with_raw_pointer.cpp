// using smart pointer to avoid dangling pointers and references.
#include <memory>
#include <iostream>

#include <stdio.h>
#include <string.h>

struct FILE_deleter {
  void operator() (FILE* fp) const {
    fclose(fp);
  }
};

int main(int argc, char *argv[])
{
  const char filename[] = "../CMakeLists.txt";
  std::shared_ptr<FILE> sp(fopen(filename, "r+"), FILE_deleter{});

  char buf[4096];
  memset(buf, 0, sizeof(buf));

  fgets(buf, sizeof(buf), sp.get()); // read at most one less than size characters
  std::cout << buf;

  return 0;
}
