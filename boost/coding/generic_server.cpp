#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <cstdint>
#include <thread>
#include <memory>

#include <boost/asio.hpp>

using namespace boost;

template <typename ConnectionHandler>
class asio_generic_server {
  using shared_handler_t = std::shared_ptr<ConnectionHandler>;

public:
  asio_generic_server(int thread_count = 1) :
    thread_count_(thread_count),
    acceptor_(io_service_)
  {}

  void start_server(uint16_t port)
  {
    auto handler =
      std::make_shared<ConnectionHandler>(io_service_);

    // set up the acceptor to listen on the tcp port
    asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), port);
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();

    acceptor_.async_accept(handler->socket(),
        [=] (auto ec) {
          handle_new_connection(handler, ec);
        });

    // start pool of threads to process the asio events
    for (int i = 0; i < thread_count_; ++i) {
      thread_pool_.emplace_back([&] { io_service_.run(); });
    }
  }

  ~asio_generic_server() {
    for (int i = 0; i < thread_count_; ++i) {
      thread_pool_[i].join();
    }
  }

private:
  void handle_new_connection(shared_handler_t handler,
      const system::error_code& error)
  {
    if (error) { return; }

    std::cout << "new connetion" << std::endl;
    handler->start();

    // make a new handler to continue on accepting new connection.
    auto new_handler =
      std::make_shared<ConnectionHandler>(io_service_);

    acceptor_.async_accept(new_handler->socket(),
        [=] (auto ec) {
          handle_new_connection(new_handler, ec);
        });
  }

  int thread_count_;
  std::vector<std::thread> thread_pool_;
  asio::io_service io_service_;
  asio::ip::tcp::acceptor acceptor_;
};

class chat_handler
  : public std::enable_shared_from_this<chat_handler>
{
public:
  chat_handler(asio::io_service& service)
    : service_(service),
      socket_(service),
      write_strand_(service)
  {}

  asio::ip::tcp::socket& socket() {
    return socket_;
  }

  void start() {
    read_packet();
  }

  void send(std::string msg) {
    service_.post(write_strand_.wrap(
          [me=shared_from_this(), msg]
          {
            me->queue_message(msg);
          }));
  }

private:
  void read_packet() {
    asio::async_read_until(socket_,
                          in_pakcet_,
                          '\n',
                          [me=shared_from_this()]
                          (system::error_code const &ec, std::size_t bytes_xfer)
                          {
                            me->read_packet_done(ec, bytes_xfer);
                          });
  }

  void read_packet_done(system::error_code const& error,
      std::size_t bytes_transferred)
  {
    if (error) { return; }

    in_pakcet_.commit(bytes_transferred);
    std::istream stream(&in_pakcet_);
    std::string packet_string;
    // stream >> packet_string; // don't ignore whitespaces
    std::getline(stream, packet_string);

    std::cout << "stream: " << packet_string << std::endl;
    // do something with it.
    send(packet_string);

    // continue to read the packet.
    read_packet();
  }

  void queue_message(std::string message) {
    bool write_in_progress = !send_packet_queue.empty();

    send_packet_queue.push_back(std::move(message));
    start_packet_send();
    // if (!write_in_progress) {
    //   start_packet_send();
    // }
  }

  void start_packet_send() {
    send_packet_queue.front() += '\0';
    async_write(socket_,
        asio::buffer(send_packet_queue.front()),
        write_strand_.wrap([me=shared_from_this()]
          (system::error_code const &ec, std::size_t)
          {
            me->packet_send_done(ec);
          }));
  }

  void packet_send_done(system::error_code ec) {
    // do nothing...
  }

  asio::io_service& service_;
  asio::ip::tcp::socket socket_;
  asio::io_service::strand write_strand_;
  asio::streambuf in_pakcet_;
  std::deque<std::string> send_packet_queue; // send every msg to every client
};

int main(int argc, char* argv[])
{
  asio_generic_server<chat_handler> server;
  server.start_server(10000);

  return 0;
}
