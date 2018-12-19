#include <iostream>
#include <thread>

// Q: it's thread-safe ?
// A: In c++11, it's thread-safe. but it's not in c++03.
// because the c++11 standard point out that:
// concurrent execution shall wait for completion of the initialization.
class Singleton
{
public:
  static Singleton& getInstance() {
    static Singleton s;
    return s;
  }

  Singleton(const Singleton&)      = delete;
  void operator=(const Singleton&) = delete;

private:
  Singleton() {}
};

int main(int argc, char *argv[])
{
  return 0;
}

