#include <iostream>
#include <exception>
#include <fstream>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

using namespace std;

int main(int argc, char** argv)
{
  namespace po = boost::program_options;

  try {

    /*
     * The option item is composed of what ?
     * <command> <type> <description>
     * <type> is ignorable, once be set, and it decides the type of command.
     */
    po::options_description general("General options");
    general.add_options()
      ("help", "produce a help message")
      (
        "help-module",
        po::value<std::string>(),
        "produce a help for given module"
      )
      ("version", "output the version number");

    po::options_description gui("GUI options");
    gui.add_options()
      ("display", po::value<std::string>(), "display to use");

    po::options_description backend("Backend options");
    backend.add_options()
      ("num-threads", po::value<int>(), "the initial number of threads");

    // Declare an options description instance which will include
    // all the options
    //
    // That looks like what ?
    // Hierarchy
    po::options_description all("Allowed options");
    all
      .add(general)
      .add(gui)
      .add(backend);

    po::options_description visible("Allowed options");
    visible.add(general).add(gui);

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, all), vm);

    if (vm.count("help"))
    {
      std::cout << visible;
      return 0;
    }

    if (vm.count("help-module"))
    {
      const string& s = vm["help-module"].as<std::string>();
      if (s == "gui") {
        std::cout << gui;
      } else if (s == "backend") {
        std::cout << backend;
      } else {
        std::cout << "Unknown module '"
                  << s << "' in the help-module option\n";
        return 1;
      }
      return 0;
    }

    if (vm.count("num-threads"))
    {
      std::cout << "The num-threads' options was set to "
                << vm["num-threads"].as<int>() << '\n';
    }

  } catch (std::exception const& e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "Unhandled exception" << std::endl;
  }

  return 0;
}

// test
// ./option_groups --help
// ./option_groups --help-module gui
// ./option_groups --help-module backend
// ./option_groups --num-threads=10
