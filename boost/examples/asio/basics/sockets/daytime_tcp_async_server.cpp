/*
 * async operations: accept and write function
 *
 * How to design the class hierarchy:
 * top -> bottom, if you meet some problem, you can try opposite way.
 *
 * so, you want to do like the following code:
 * tcp_server server(io_context);
 *
 * so, the tcp_server will accept the incoming connections, and deal with them.
 *
 * How can we do ?
 * tcp_server deal with the incoming connections, we abstract tcp_connection.
 * and tcp_connection send current time as a string to client.
 *
 * we don't need to extract tcp_connection, but it makes the business clear.
 */
#include <ctime>
#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
  using namespace std;
  time_t now = time(0);
  return ctime(&now);
}

class tcp_connection
  : public boost::enable_shared_from_this<tcp_connection>
{
public:
  typedef boost::shared_ptr<tcp_connection> pointer;

  static pointer create(boost::asio::io_context& io_context)
  {
    return pointer{new tcp_connection(io_context)};
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  void start()
  {
    message_ = make_daytime_string();

    // use async_write() to ensure that the entire block of data is sent,
    // compare with async_write_some()
    boost::asio::async_write(socket_, boost::asio::buffer(message_),
        boost::bind(&tcp_connection::handle_write, shared_from_this(),
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

private:
  tcp_connection(boost::asio::io_context& io_context)
    : socket_{io_context}
  {}

  void handle_write(const boost::system::error_code& /*error*/,
      size_t /* bytes_transferred */)
  {
  }

  tcp::socket socket_;
  std::string message_;
};

class tcp_server
{
public:
  tcp_server(boost::asio::io_context& io_context)
    : acceptor_{io_context, tcp::endpoint(tcp::v4(), 13)}
  {
    start_accept();
  }

private:
  void start_accept()
  {
    tcp_connection::pointer new_connection =
      tcp_connection::create(acceptor_.get_executor().context());

    acceptor_.async_accept(new_connection->socket(),
        boost::bind(&tcp_server::handle_accept, this, new_connection,
          boost::asio::placeholders::error));
  }

  void handle_accept(tcp_connection::pointer new_connection,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      new_connection->start();
    }

    start_accept();  // infinite loop to accept new connection
  }

  tcp::acceptor acceptor_;
};

int main(int argc, char** argv)
{
  try
  {
    boost::asio::io_context io_context;
    tcp_server server{io_context};
    io_context.run();
  }
  catch (std::exception const& e)
  {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
