/*
 * Make clear the difference between TCP and UDP
 */
#include <iostream>

#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main(int argc, char** argv)
{
  try
  {
    if (argc != 2)
    {
      std::cout << "Usage: " << argv[0] << " host\n";
      return 1;
    }

    boost::asio::io_context io_context;

    udp::resolver resolver{io_context};
    udp::endpoint receiver_endpoint =
      *resolver.resolve(udp::v4(), argv[1], "daytime").begin();

    udp::socket socket{io_context};
    socket.open(udp::v4());

    boost::array<char, 128> send_buf = {{ 0 }};
    socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

    boost::array<char, 128> recv_buf;
    udp::endpoint sender_endpoint;
    size_t len = socket.receive_from(
        boost::asio::buffer(recv_buf), sender_endpoint);

    std::cout.write(recv_buf.data(), len);
  }
  catch (std::exception const & e)
  {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
