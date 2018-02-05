#include <iostream>

#include <boost/filesystem.hpp>

#define BOOST_FILESYSTEM_NO_DEPRECATED

int main(int argc, char** argv)
{
  using namespace boost::filesystem;

  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << "path\n";
    return 1;
  }

  path p(argv[1]);

  if (exists(p))
  {
    if (is_regular_file(p))
      std::cout << p << " size is " << file_size(p) << '\n';
    else if (is_directory(p))
      std::cout << p << " exists, is a directory\n";
    else
      std::cout << p << " exists, but is not a regular file or directory\n";
  }
  else
  {
    std::cout << p << " does not exist\n";
  }

  return 0;
}
