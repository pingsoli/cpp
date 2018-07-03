#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

int main(int argc, char *argv[])
{
  auto day = 24h;
  std::cout << day.count() << '\n';

  std::cout << std::chrono::duration_cast<std::chrono::minutes>(day).count()
    << std::endl;

  return 0;
}
