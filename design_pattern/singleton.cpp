#include "singleton.h"

int main(int argc, char** argv)
{
  Singleton& s = Singleton::getInstance();

  return 0;
}
