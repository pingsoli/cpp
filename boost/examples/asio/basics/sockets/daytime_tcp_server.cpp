#include <ctime>
#include <iostream>
#include <string>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_daytime()
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

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

    for (;;)
    {
      tcp::socket socket(io_context);
      acceptor.accept(socket);

      std::string message = make_daytime();

      boost::system::error_code ignored_error;
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
  }
  catch (std::exception const& e)
  {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
