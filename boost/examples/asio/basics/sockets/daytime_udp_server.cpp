#include <ctime>
#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::udp;

std::string make_daytime_string()
{
  using namespace std;
  time_t now = time(0);
  return ctime(&now);
}

int main(int argc, char** argv)
{
  try
  {
    boost::asio::io_context io_context;

    // why port number is 13 ?
    // because 13 is reserved port number for tcp and udp. now we don't use
    // custom port number.
    udp::socket socket(io_context, udp::endpoint(udp::v4(), 13));

    for (;;)
    {
      boost::array<char, 1> recv_buf;
      udp::endpoint remote_endpoint;
      boost::system::error_code error;
      socket.receive_from(boost::asio::buffer(recv_buf),
          remote_endpoint, 0, error);

      if (error && error != boost::asio::error::message_size)
        throw boost::system::system_error(error);

      std::string message = make_daytime_string();

      boost::system::error_code ignored_error;
      socket.send_to(boost::asio::buffer(message),
          remote_endpoint, 0, ignored_error);
    }
  }
  catch (std::exception const & e)
  {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
