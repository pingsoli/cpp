#include <iostream>
#include <thread>

void hello()
{
  std::cout << "Hello Concurrent World!\n";
}

int main(int argc, char** argv)
{
  std::thread t1(hello);
  std::thread t2(hello);

  t1.join();
  t2.join();

  return 0;
}
