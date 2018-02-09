#include <cstdlib>
#include <iostream>
#include <string>

#include <boost/asio.hpp>

using boost::asio::ip::udp;

enum { max_length = 1024 };

void server(boost::asio::io_context& io_context, unsigned short port)
{
  udp::socket socket(io_context, udp::endpoint(udp::v4(), port));
  for (;;)
  {
    char data[max_length];
    udp::endpoint sender_endpoint;

    std::size_t length = socket.receive_from(
        boost::asio::buffer(data, max_length), sender_endpoint);
    socket.send_to(boost::asio::buffer(data, length), sender_endpoint);
  }
}

int main(int argc, char** argv)
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: <server> <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;
    server(io_context, std::atoi(argv[1]));
  }
  catch (std::exception const& e)
  {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
