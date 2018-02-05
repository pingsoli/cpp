/*
 * Features:
 *   type-safe and extensible
 *
 * Details:
 *   operator %, and get formated string
 *
 * Performance
 *   I really care about the performance of boost.format ?
 *   Official docs say reoderding overhead, it will be slower noticealy than
 *   printf() function, expects a ratio ranging 2 to 5 or more.
 */
#include <iostream>
#include <iomanip>

#include <boost/format.hpp>

namespace MyNS_ForOutput {
  using std::cout; using std::cerr;
  using std::string;
  using std::endl; using std::flush;

  using boost::format;
  using boost::io::group;
}

namespace MyNS_Manips {
  using std::setfill;
  using std::setw;
  using std::hex;
  using std::dec;
}

int main(int argc, char** argv)
{
  using namespace MyNS_ForOutput;
  using namespace MyNS_Manips;

  // It's ugly
  std::cout << format("%|1$1| %|2$3|") % "Hello" % 3 << std::endl;
  // Hello   3

  // More elegant
  std::cout << format{"%1%.%2%.%3%"} % 12 % 5 % "2014" << '\n';
  // 12.5.2014

  // So, how it works ?
  format fm("%1%.%2%.%3%");
  fm % 12; fm % 5; fm % "2014";
  cout << fm.str() << endl;
  // 12.5.2014

  // More precise formatting
  cout << format("(x,y) = (%1$+5d,%2$+5d) \n") % -23 % 35;  // Posix-Printf
  // (x,y) = (  -23,  +35) 

  // Using manipulators, via 'group'
  std::cout << format("%2% %1% %2%\n")
                 % 1
                 % group(setfill('X'), hex, setw(4), 16+3);
  // XX13 1 XX13

  // Handling exceptions
  try
  {
    format(" %1 %1 ") % 101 % 102;
    format(" %4% ") % 101;  // it won't give any exception warning
  }
  catch (boost::io::too_many_args& e)
  {
    cerr << e.what() << endl;
  }
  catch (boost::io::too_few_args& e)
  {
    cerr << e.what() << endl;
  }
  catch (std::exception const& e)
  {
    cerr << e.what() << endl;
  }

  return 0;
}
