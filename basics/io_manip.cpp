#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void state()
{
  std::cout << "\n"
               "Bad: " << std::cin.bad() << " "
               "Fial: " << std::cin.fail() << " "
               "Eof: " << std::cin.eof() << " "
               "Good: " << std::cin.good() << "\n";
}

void io_conidtion_test()
{
  std::string line;
  int x;

  std::cin >> x;
  state();

  std::cin.clear();
  getline(std::cin, line);
  state();

  getline(std::cin, line);
  state();
}

void rw_file()
{
  fstream rw("test", ios::out | ios::in);

  if (!rw)       // file don't exist yet
  {
    rw.clear();  // try again, creating it: bail out
    rw.open("test", ios::out | ios::trunc | ios::in);
  }

  if (!rw)
  {
    cerr << "Opening test file failed miserably" << '\n';
    return;
  }

  cerr << "We're at: " << rw.tellp() << '\n';
  rw << "Hello world" << '\n';

  rw.seekg(0);  // go back and read what's written

  string s;
  getline(rw, s);

  cout << "Read: " << s << '\n';
}

int main(int argc, char** argv)
{
  return 0;
}
