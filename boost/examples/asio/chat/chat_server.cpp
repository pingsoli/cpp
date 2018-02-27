/*
 ***********************************************************************
 * chat_session:
 *   deal with the connection
 *   decode header -> decode body -> write message
 *
 * chat_room:
 *   it likes a container, manage all chat_sessions.
 *   participant can join the chat_room, leave.
 *   chat_room delivery message to every participant.
 *
 * chat_server:
 *   accept the new connection, and start to deal with it
 *
 * Observer Design Pattern
 *   chat_session is Observer.
 *   chat_room is Subject.
 * in UML, chat_session and chat_room are aggregation relatioship.
 *
 ***********************************************************************
 * Sumary:
 * chat_session 'is a' chat_participant, can be joined into chat_room,
 * chat_room 'has' multiple chat_session
 *
 ***********************************************************************
 * Undergoing:
 * 1) callback function parameter add reference
 *    [](boost::system::error_code& ec, std::size_t ) {}  // Error
 *    incurred many strange errors in g++, but located the error place.
 *
 ***********************************************************************
 */
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <utility>
#include <set>

#include <boost/asio.hpp>
#include "chat_message.hpp"

using boost::asio::ip::tcp;
typedef std::deque<chat_message> chat_message_queue;

//////////////////////////////////////////////////////////////////////

class chat_participant
{
public:
  virtual ~chat_participant() {}
  virtual void deliver(const chat_message& msg) = 0;
};

//////////////////////////////////////////////////////////////////////

typedef std::shared_ptr<chat_participant> chat_participant_ptr;

class chat_room
{
public:
  // Deliver all recent messages to a joining participant
  void join(chat_participant_ptr participant)
  {
    participants_.insert(participant);
    for (auto msg: recent_msgs_)
      participant->deliver(msg);
  }

  void leave(chat_participant_ptr participant)
  {
    participants_.erase(participant);
  }

  void deliver(const chat_message& msg)
  {
    recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > max_recent_msgs)
      recent_msgs_.pop_front();

    for (auto participant : participants_)
      participant->deliver(msg);
  }

private:
  std::set<chat_participant_ptr> participants_;
  enum { max_recent_msgs = 100 };
  chat_message_queue recent_msgs_;
};

//////////////////////////////////////////////////////////////////////

class chat_session
  : public chat_participant,
    public std::enable_shared_from_this<chat_session>
{
public:
  chat_session(tcp::socket socket, chat_room& room)
    : socket_{std::move(socket)},
      room_{room}
  {
  }

  void start()
  {
    room_.join(shared_from_this());
    do_read_header();
  }

  void deliver(const chat_message& msg)
  {
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
    {
      do_write();
    }
  }

private:
  void do_read_header()
  {
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.data(), chat_message::header_length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec && read_msg_.decode_header())
          {
            do_read_body();
          }
          else
          {
            room_.leave(shared_from_this());
          }
        });
  }

  void do_read_body()
  {
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            room_.deliver(read_msg_);
            do_read_header();
          }
          else
          {
            room_.leave(shared_from_this());
          }
        });
  }

  void do_write()
  {
    auto self(shared_from_this());
    boost::asio::async_write(socket_,
        boost::asio::buffer(write_msgs_.front().data(),
          write_msgs_.front().length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            write_msgs_.pop_front();
            if (!write_msgs_.empty())
            {
              do_write();
            }
          }
          else
          {
            room_.leave(shared_from_this());
          }
        });
  }

  tcp::socket        socket_;
  chat_room&         room_;
  chat_message       read_msg_;
  chat_message_queue write_msgs_;
};

//////////////////////////////////////////////////////////////////////

class chat_server
{
public:
  chat_server(boost::asio::io_context& io_context,
      const tcp::endpoint& endpoint)
    : acceptor_{io_context, endpoint}
  {
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
          // print remote ip and port info
          std::string remote_ip_address =
            socket.remote_endpoint().address().to_string();
          unsigned int remote_port = socket.remote_endpoint().port();

          std::cout << "Accepted a new client from "
            << "[ " << remote_ip_address << " : " << remote_port << " ]\n";

          if (!ec)
          {
            std::make_shared<chat_session>(std::move(socket), room_)->start();
          }

          do_accept();
        });
  }

  tcp::acceptor acceptor_;
  chat_room     room_;
};

//////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  try
  {
    if (argc < 2)
    {
      std::cerr << "Usage: chat_server <port> [<port> ...]\n";
      return 1;
    }

    boost::asio::io_context io_context;

    std::list<chat_server> servers;
    for (int i = 0; i < argc; ++i)
    {
      tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[i]));
      servers.emplace_back(io_context, endpoint);
    }

    io_context.run();
  }
  catch (std::exception const& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
