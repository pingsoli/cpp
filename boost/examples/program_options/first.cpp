/*
 * What should we konow about boost program_options ?
 * Three components:
 *   1) The options description component (opstions_description)
 *   2) The parsers component (parse_command_line)
 *   3) The storage component (variables_map)
 */
#include <iostream>
#include <iterator>

#include <boost/program_options.hpp>

int main(int argc, char** argv)
{

  try {
    namespace po = boost::program_options;

    po::options_description desc("Allowed options");

    desc.add_options()
      ("hello", "produce help message")
      ("compression", po::value<double>(), "set compression level");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
      std::cout << desc << '\n';
      return 0;
    }

    if (vm.count("compression")) {
      std::cout << "Compression level was set to "
                << vm["compression"].as<double>() << '\n';
    } else {
      std::cout << "Compression level was not set.\n";
    }

  } catch (std::exception const& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  } catch (...) {
    std::cout << "unhandled exception" << std::endl;
  }

  return 0;
}

// output:
// ./first --compression=5.5
// ./first --compression 5.5
// Compression level was set to 5.5
//
// ./first --compression h
// Error: the argument ('h') for option '--compression' is invalid
