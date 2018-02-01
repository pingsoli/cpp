/*
 * string to number
 *
 * istringstream is too powerful, so we don't use it.
 */
#include <boost/lexical_cast.hpp>
#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
  using boost::lexical_cast;
  using boost::bad_lexical_cast;

  std::vector<short> args;

  while (*++argv) {
    try {
      args.push_back(lexical_cast<short>(*argv));
    } catch (bad_lexical_cast&) {
      args.push_back(0);
    }
  }

  for (const short v: args)
    std::cout << v << " ";

  std::cout << std::endl;
  return 0;
}
