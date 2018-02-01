#include <iostream>
#include <algorithm>
#include <iterator>

#include <boost/program_options.hpp>

using namespace std;

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
  std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
  return os;
}

int main(int argc, char** argv)
{
  namespace po = boost::program_options;

  try {
    int opt;
    int portnum;

    po::options_description desc("Allowed options");
    /*
     * The difference between implicit_value and default_value ?
     */
    desc.add_options()
      ("help", "produce help message")
      (
        "optimization",
        po::value<int>(&opt)->default_value(10),
        "optimization level"
      )
      (
        "verbose,v",
        po::value<int>()->implicit_value(1),
        "enable verbosity (optionally specify level)"
      )
      (
        "listen",
        po::value<int>(&portnum)->implicit_value(1001)
          ->default_value(0, "no"),
        "listen on a port"
      )
      (
        "include-path,I",
        po::value<std::vector<std::string>>(),
        "include path"
      )
      (
        "input-file",
        po::value<std::vector<std::string>>(),
        "input file"
      );

    // Guess option names for positional options.
    // value '-1' means 'unlimited', the place of input-file option
    // can be in arbitrary place.
    //
    // if the number is positive, like:
    // p.add("output-file", 2);
    //
    // we must specify output-file options in first two place.
    po::positional_options_description p;
    p.add("input-file", -1);

    po::variables_map vm;
    po::store(
      po::command_line_parser(argc, argv)
      .options(desc)
      .positional(p)
      .run(),
      vm
    );

    // What the meaning of notify ? why need this ?
    //
    // Offical docs say: calls store.parse_command_line and notify functions
    // cause vm to cantain all the options found on the command line.
    //
    // So, store() and notify() are couple. I did not dive deep.
    po::notify(vm);

    if (vm.count("help")) {
      std::cout << "Usage: options_descriptions [options]\n";
      std::cout << desc;
      return 0;
    }

    if (vm.count("include-path")) {
      std::cout << "Include paths are: "
                << vm["include-path"].as<std::vector<std::string>>() << '\n';
    }

    if (vm.count("input-file")) {
      std::cout << "Input files are: "
                << vm["input-file"].as<std::vector<std::string>>() << '\n';
    }

    if (vm.count("verbose")) {
      std::cout << "Verbosity enabled. Level is " << vm["verbose"].as<int>()
                << '\n';
    }

    std::cout << "Optimization level is " << opt << '\n';
    std::cout << "Listen port is " << portnum << '\n';

  } catch (std::exception const& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
