#include <iostream>
#include <exception>
#include <string>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

/*
 * What the extra parser do ?
 * Every options will be parsered,
 * this custom option parse function recongnize
 * option "-ffoo" / "-fno-foo"
 *
 * Why reg_foo() function return a std::pair<string, string> ?
 * It depends on interface implemented by boost library, contains
 * the option name and value.
 *
 * Testing:
 *
 * ./custom_syntax --foo hello
 * foo value with the value of hello
 *
 * ./custom_syntax -fno-foo
 * foo value with the value of false
 *
 * ./custom_syntax -ffoo
 * foo value with the value of true
 */
std::pair<std::string, std::string>
reg_foo(std::string const& s)
{
  using namespace std;

  if (s.find("-f") == 0) {
    if (s.substr(2, 3) == "no-")
      return make_pair(s.substr(5), string("false"));
    else
      return make_pair(s.substr(2), string("true"));
  } else {
    return make_pair(string(), string());
  }
}

int main(int argc, char** argv)
{
  namespace po = boost::program_options;

  try {
    po::options_description desc("Allowed options");
    desc.add_options()
      ("help", "produce a help message")
      ("foo", po::value<std::string>(), "just an option");

    po::variables_map vm;
    po::store(
      po::command_line_parser(argc, argv)
      .options(desc)
      .extra_parser(reg_foo)  // Here is your own additional parser
      .run(), vm
    );

    if (vm.count("help")) {
      std::cout << desc;
      std::cout << "\nIn addition -ffoo and -fno-foo syntax are recongized\n";
    }

    if (vm.count("foo")) {
      std::cout << "foo value with the value of "
                << vm["foo"].as<std::string>() << '\n';
    }

  } catch (std::exception const& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  } catch (...) {
    std::cerr << "unhandled error message" << std::endl;
  }

  return 0;
}
