#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/filesystem.hpp>

int main(int argc, char** argv)
{
  using namespace boost::filesystem;

  if (argc < 2)
  {
    std::cerr << "Usage: tut4 path\n";
    return 1;
  }

  path p(argv[1]);

  try
  {
    if (exists(p))
    {
      if (is_regular_file(p))
        std::cout << p << " size is " << file_size(p) << '\n';
      else if (is_directory(p))
      {
        std::cout << p << " is a directory containing: \n";

        std::vector<path> v;

        for (auto && x: directory_iterator(p))
          v.push_back(x.path());

        std::sort(v.begin(), v.end());

        for (auto && x: v)
          std::cout << "    " << x.filename() << '\n';
      }
      else
        std::cout << p << " exists, but is not a regular file or directory\n";
    }
    else
      std::cout << p << " does not exist\n";
  }
  catch (filesystem_error const& e)
  {
    std::cerr << e.what() << '\n';
  }

  return 0;
}
