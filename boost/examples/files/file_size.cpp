#include <iostream>

#include <boost/filesystem.hpp>

#define BOOST_FILESYSTEM_NO_DEPRECATED

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " path\n";
    return 1;
  }

  std::cout << argv[1] << " " << boost::filesystem::file_size(argv[1]) << '\n';
  return 0;
}
