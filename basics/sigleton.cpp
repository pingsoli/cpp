#include <iostream>
#include <thread>

// Q: it's thread-safe ?
// A: In c++11, it's thread-safe. but in c++03, it's not.
// because the c++11 standard point out that:
// concurrent execution shall wait for completion of the initialization.
class Sigleton
{
public:
  static Sigleton& getInstance() {
    static Sigleton s;
    return s;
  }

  Sigleton(const Sigleton&)       = delete;
  void operator=(const Sigleton&) = delete;

private:
  Sigleton() {}
};

int main(int argc, char *argv[])
{
  return 0;
}
