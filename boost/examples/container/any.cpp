////////////////////////////////////////////////////////////////////////////////
// Don't care about type, you can store any type you wish.
// int, bool, float, double or std container.
//
// Implementation details:
// http://www.two-sdg.demon.co.uk/curbralan/papers/ValuedConversions.pdf
//
// boost::any VS. boost::variant ?
// http://www.boost.org/doc/libs/1_66_0/doc/html/variant/misc.html#variant.versus-any
//
// boost::any can be used in std::map ?
// Yes, of course, but you must implement your own compare function.
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>

#include <boost/any.hpp>

int main(int argc, char** argv)
{
  try
  {
    //////////////////////////////////////////////////////////////////////
    // vice-versa
    // Store any type you wish
    boost::any a = 1;
    std::cout << boost::any_cast<int>(a) << '\n';

    a = 3.14;
    std::cout << boost::any_cast<double>(a) << '\n';

    a = true;
    std::cout << std::boolalpha << boost::any_cast<bool>(a) << '\n';

    a = std::string("hello world");
    std::cout << boost::any_cast<std::string>(a) << '\n';

    // Convert to real-type
    boost::any z = 1;
    int *i = boost::any_cast<int>(&z);
    std::cout << *i << '\n';
    //////////////////////////////////////////////////////////////////////

    // Get the type name
    if (!a.empty())
    {
      const std::type_info &ti = a.type();
      std::cout << ti.name() << '\n';
    }
    // NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
    // It looks obscure, need focus on it.

    // invalid conversion
    boost::any x = 1;
    std::cout << boost::any_cast<float>(a) << '\n';
  }
  catch (boost::bad_any_cast const& e)
  {
    std::cout << e.what() << std::endl;
  }
  catch (std::exception const& e)
  {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
