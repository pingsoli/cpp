/*
 * Synchronising hanlders in multithread programs
 * boost::asio::io_service::strand usage
 * guarantee stranded works executed linearly, won't be concurrently.
 */
#include <iostream>

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// use strand to guarantee two handlers cannot be executed concurrently
// though counter_ is not thread-safe, the function scope is the strand_
// ctritical area
class printer
{
public:
  printer(boost::asio::io_context& io) :
    strand_{io},
    timer1_{io, boost::posix_time::seconds(1)},
    timer2_{io, boost::posix_time::seconds(1)},
    counter_{0}
  {
    timer1_.async_wait(boost::bind(&printer::print1, this));
    timer2_.async_wait(boost::bind(&printer::print2, this));
  }

  ~printer()
  {
    std::cout << "Fianl counter is " << counter_ << std::endl;
  }

  void print1()
  {
    if (counter_ < 10)
    {
      std::cout << "Timer 1: " << counter_ << std::endl;
      ++counter_;

      timer1_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));

      // different with before, the bind_executor function return a new handler
      // that dispatatched automatically through
      // boost::asio::io_service::strand object.
      timer1_.async_wait(boost::asio::bind_executor(strand_,
            boost::bind(&printer::print1, this)));
    }
  }

  void print2()
  {
    if (counter_ < 10)
    {
      std::cout << "Timer 2: " << counter_ << std::endl;
      ++counter_;

      timer2_.expires_at(timer2_.expires_at() + boost::posix_time::seconds(1));
      timer2_.async_wait(boost::asio::bind_executor(strand_,
            boost::bind(&printer::print2, this)));
    }
  }

private:
  boost::asio::io_context::strand strand_;
  boost::asio::deadline_timer timer1_;
  boost::asio::deadline_timer timer2_;
  int counter_;  // it's not atomic
};

int main(int argc, char** argv)
{

  boost::asio::io_context io;
  printer p{io};
  boost::thread t(boost::bind(&boost::asio::io_context::run, &io));

  io.run();
  t.join();

  return 0;
}
