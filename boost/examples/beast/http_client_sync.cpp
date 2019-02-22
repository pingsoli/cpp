// HTTP sync client

// Simulate HTTP server
// $ python -m http.server

#include <cstdlib>
#include <iostream>
#include <string>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

int main(int argc, char *argv[])
{
  try {
    const std::string host   = "0.0.0.0";
    const std::string port   = "8000";
    const std::string target = "/";
    const int version        = 11;

    // The io_context is required for all I/O
    net::io_context ioc;

    tcp::resolver resolver{ioc};
    tcp::socket socket{ioc};

    // Look up the domain name
    auto const results = resolver.resolve(host, port);
    net::connect(socket, results.begin(), results.end());

    // Set up an HTTP GET request to the remote host
    http::request<http::string_body> req{http::verb::get, target, version};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    // Send the HTTP request to the remote host
    http::write(socket, req);

    // This buffer is used for reading and must be persisted
    beast::flat_buffer buffer;

    // Declare a container to hold the response
    http::response<http::dynamic_body> res;

    // Receive the HTTP response
    http::read(socket, buffer, res);

    std::cout << res << '\n';

    // Gracefully close the socket
    beast::error_code ec;
    socket.shutdown(tcp::socket::shutdown_both, ec);

    if (ec && ec != beast::errc::not_connected)
      throw beast::system_error{ec};

  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
