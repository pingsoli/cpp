/*
 *           |- generic
 * visible --|
 *           |- config
 *
 *                   |- generic
 * cmdline_options --|- config
 *                   |- hidden
 *
 *                       |- config
 * config_file_options --|
 *                       |- hidden
 *
 * Hierarchy Level
 * merge options into different combinations
 */

#include <iostream>
#include <fstream>
#include <iterator>

#include <boost/program_options.hpp>

using namespace std;

template <typename T>
std::ostream& operator<<(ostream& os, const std::vector<T>& v)
{
  std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
  return os;
}

int main(int argc, char** argv)
{
  try {
    int opt;
    std::string config_file;

    namespace po = boost::program_options;

    po::options_description generic("Generic options");
    generic.add_options()
      ("version,V", "print version string")
      ("help", "produce help message")
      (
        "config,c",
         po::value<std::string>(&config_file)
                           ->default_value("../multiple_sources.cfg"),
        "name of a file of a configuration."
      );

    po::options_description config("Configuration");
    config.add_options()
      (
        "optimization",
        po::value<int>(&opt)->default_value(10),
        "optimization level"
      )
      (
        "include-path,I",
        po::value<vector<std::string>>()->composing(),
        "include path"
      );

    po::options_description hidden("Hidden options");
    hidden.add_options()
      ("inpue-file", po::value<vector<std::string>>(), "input file");

    po::options_description cmdline_options;
    cmdline_options
      .add(generic)
      .add(config)
      .add(hidden);

    po::options_description config_file_options;
    config_file_options
      .add(config)
      .add(hidden);

    po::options_description visible("Allowed options");
    visible
      .add(generic)
      .add(config);

    po::positional_options_description p;
    p.add("input-file", -1);

    po::variables_map vm;
    po::store(
      po::command_line_parser(argc, argv)
        .options(cmdline_options)
        .positional(p)
        .run(),
      vm);
    notify(vm);

    this is a test fiel

    std::ifstream ifs(config_file.c_str());
    if (!ifs) {
      std::cout << "can not open config file: " << config_file << '\n';
      return 0;
    } else {
      po::store(parse_config_file(ifs, config_file_options), vm);
      notify(vm);
    }

    if (vm.count("help")) {
      std::cout << visible << '\n';
      return 0;
    }

    if (vm.count("version")) {
      std::cout << "Multiple sources example, version 1.0\n";
      return 0;
    }

    if (vm.count("include-path")) {
      std::cout << "Include paths are: "
                << vm["include-path"].as<vector<std::string>>() << '\n';
    }

    std::cout << "Optimization level is " << opt << '\n';
  } catch (std::exception const& e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "unhandled exception." << std::endl;
  }

  return 0;
}
