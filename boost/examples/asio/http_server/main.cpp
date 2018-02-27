#include <iostream>
#include <iomanip>
#include <string>
#include <boost/asio.hpp>

#include "server.hpp"

int main(int argc, char** argv)
{
  try
  {
    // Check command line arguments
    if (argc != 4)
    {
      std::cerr << "Usage: http_server <address> <port> <doc_root>\n";
      std::cerr << "    For IPv4, try:\n";
      std::cerr << "      receive 0.0.0.0 80.\n";
      std::cerr << "    For Ipv6, try:\n";
      std::cerr << "      receive 0::0 80.\n";
      return 1;
    }

    // Initialise the server
    http::server::server s(argv[1], argv[2], argv[3]);

    // Print server info
    std::cout
      << std::setw(10) << std::left << "address: "  << argv[1] << '\n'
      << std::setw(10) << std::left << "port: "     << argv[2] << '\n'
      << std::setw(10) << std::left << "doc_root: " << argv[3] << '\n';

    // Run the server until stopped
    s.run();
  }
  catch (std::exception const& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
  return 0;
}
