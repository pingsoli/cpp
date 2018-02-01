/*
 * Checking and judging whether the options exist conflicts.
 * the options may has dependencies, so, we can check it.
 *
 * Following code will do the above thing.
 */
#include <iostream>

#include <boost/program_options.hpp>

using namespace std;
using namespace boost::program_options;

/*
 * Auxiliary functions for checking input for validity.
 *
 * Function used to check that 'opt1' and 'opt2' are not specified
 * at the same time.
 */
void conflicting_options(const variables_map& vm,
    const char* opt1, const char* opt2)
{
  if (
      vm.count(opt1) && !vm[opt1].defaulted() &&
      vm.count(opt2) && !vm[opt2].defaulted()
     )
    throw logic_error(string("Conflicting options '")
        + opt1 + "' and '" + opt2 + "'.");
}

void option_dependency(const variables_map& vm,
    const char* for_what, const char* required_option)
{
  if (vm.count(for_what) && !vm[for_what].defaulted())
  {
    if (vm.count(required_option) == 0 || vm[required_option].defaulted())
      throw logic_error(string("Option '") + for_what
          + "' requires option '" + required_option + "'.");
  }
}

int main(int argc, char** argv)
{
  try {
    string ofile;
    string macrofile, libmakefile;
    bool t_given = false;
    bool b_given = false;
    string mainpackage;
    string depends = "deps_file";
    string sources = "src_file";
    string root = ".";

    options_description desc("Allowed options");
    desc.add_options()
      ("help,h", "print usage message")
      ("output,o", value(&ofile), "pathname name/short name")
      ("macrofile,m", value(&macrofile), "full pathname of macro.h")
      ("two,t", bool_switch(&t_given), "preprocess both header and body")
      ("body,b", bool_switch(&b_given), "preprocess body in header context")
      (
        "libmakfile,l",
        value(&libmakefile),
        "write include makefile for library"
      )
      ("mainpackage,p", value(&mainpackage), "output dependency information")
      ("depends,d", value(&depends), "write dependencies to <pathname>")
      ("sources,s", value(&sources), "write some package list to <pathname>")
      ("root,r", value(&root), "tread <dirname> as project root directory");

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);

    if (vm.count("help"))
    {
      std::cout << desc << '\n';
      return 0;
    }

    conflicting_options(vm, "output", "two");
    conflicting_options(vm, "output", "body");
    conflicting_options(vm, "output", "mainpackage");
    conflicting_options(vm, "two", "mainpackage");
    conflicting_options(vm, "body", "mainpackage");

    conflicting_options(vm, "two", "body");
    conflicting_options(vm, "libmakfile", "mainpackage");
    conflicting_options(vm, "libmakfile", "mainpackage");

    option_dependency(vm, "depends", "mainpackage");
    option_dependency(vm, "sources", "mainpackage");
    option_dependency(vm, "root", "mainpackage");

    cout << "two = " << vm["two"].as<bool>() << '\n';

  } catch (std::exception const &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
