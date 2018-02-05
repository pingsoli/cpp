/*
 * Recursively print directory tree.
 */
#include <iostream>
#include <exception>

#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>

int main(int argc, char** argv)
{
  using namespace boost::filesystem;

  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " path\n";
    return 1;
  }

  boost::system::error_code ec;
  for (recursive_directory_iterator it(argv[1]);
      it != recursive_directory_iterator();
      )
  {
    for (int i = 0; i <= it.level(); ++i)
      std::cout << "  ";

    std::cout << it->path() << '\n';

    it.increment(ec);
  }

  return 0;
}
