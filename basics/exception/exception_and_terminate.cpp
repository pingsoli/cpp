#include <thread>

void foo() {
  throw 1;
}

int main(int argc, char *argv[])
{
  auto t = std::thread([]{
    foo();
  });

  t.join();
  return 0;
}
