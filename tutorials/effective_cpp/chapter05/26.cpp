///////////////////////////////////////////////////////////////////////////////
//
// Item 26: Postpone variable declarations as long as possible
//
// Postpone variable definitions as long as possible. It increases program
// clarity and improves program effeciency.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

std::string encryptPassword(const std::string& password)
{
  // do something, such as validate the password

  // define and initialize via copy constructor
  std::string encrypted(password);

  // encrypt the password

  return encrypted;
}

int main(int argc, char** argv)
{
  std::string password("hello");
  std::string encrpyted;

  encryptPassword(password);

  return 0;
}
