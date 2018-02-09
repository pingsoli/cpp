#include <cstdlib>
#include <iostream>
#include <string>

#include <boost/asio.hpp>

using boost::asio::ip::udp;
enum { max_length = 1024 };

int main(int argc, char** argv)
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: <client> <host> <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;
    udp::socket socket(io_context, udp::endpoint(udp::v4(), 0));

    udp::resolver resolver(io_context);
    udp::resolver::results_type endpoints =
      resolver.resolve(udp::v4(), argv[1], argv[2]);

    std::cout << "Enter message: ";
    char request[max_length];
    std::cin.getline(request, max_length);
    std::size_t request_length = std::strlen(request);

    socket.send_to(
        boost::asio::buffer(request, request_length), *endpoints.begin());

    char reply[max_length];
    udp::endpoint sender_point;

    std::size_t reply_length = socket.receive_from(
        boost::asio::buffer(reply, max_length), sender_point);

    std::cout << "Reply: ";
    std::cout.write(reply, reply_length);
    std::cout << '\n';
  }
  catch (std::exception const& e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
