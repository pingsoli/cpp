// HTTP async client
//
// NOTE:
// the code won't compile, tcp_stream has not accepted in boost 1.69.0

#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>
#include <functional>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

using stream_type = beast::tcp_stream<net::io_context::executor_type>;

void fail(beast::error_code ec, const char* what)
{
  std::cerr << what << ": " << ec.message() << std::endl;
}

class session : public std::enable_shared_from_this<session>
{
private:
  tcp::resolver resolver_;
  stream_type stream_;
  beast::flat_buffer buffer_;
  http::request<http::empty_body> req_;
  http::response<http::string_body> res_;

public:
  explicit session(net::io_context& ioc)
    : resolver_(ioc),
      stream_(ioc)
  {
  }

  void run(const std::string& host, const std::string& port
      const std::string& target, int version)
  {
    req_.version(version);
    req_.method(http::verb::get);
    req_.target(target);
    req_.set(http::field::host, host);
    req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    // Look up the domain name
    resolver_.async_resolve(host, port,
        beast::bind_front_handler(&session::on_resolve, shared_from_this()));
  }

  void on_resolve(beast::error_code ec, tcp::resolver::results_type results)
  {
    if (ec)
      return fail(ec, "resolve");

    // Set a timeout on the operation
    stream_.expires_after(std::chrono::seconds(30));

    beast::async_connect(stream_, results,
        beast::bind_front_handler(&session::on_connect, shared_from_this()));
  }

  void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type)
  {
    if (ec)
      return fail(ec, "connect");

    // Set a timeout on the operation
    stream_.expires_after(std::chrono::seconds(30));

    // Send the HTTP request to the remote host
    http::async_write(stream_, req_,
        beast::bind_front_handler(&session::on_write, shared_from_this()));
  }

  void on_write(beast::error_code ec, std::size_t bytes_transferred)
  {
    boost::ignore_unused(bytes_transferred);

    if (ec)
      return fail(ec, "write");

    // Receive the HTTP response
    http::async_read(stream_, buffer_, res_,
        beast::bind_front_handler(&session::on_read, shared_from_this()));
  }

  void on_read(beast::error_code ec, std::size_t bytes_transferred)
  {
    boost::ignore_unused(bytes_transferred);

    if (ec)
      return fail(ec, "read");

    std::cout << res_ << '\n';

    stream_.socket().shutdown(tcp::socket::shutdown_both, ec);

    if (ec && ec != beast::errc::not_connected)
      return fail(ec, "shutdown");
  }
};

int main(int argc, char *argv[])
{

  const std::string host   = "0.0.0.0";
  const std::string port   = "8000";
  const std::string target = "/";
  const int version        = 11;

  net::io_context ioc;

  std::make_shared<session>(ioc)->run(host, port, target, version);

  // Run the I/O service. The call will return when the get operation is complete
  ioc.run();

  return 0;
}
