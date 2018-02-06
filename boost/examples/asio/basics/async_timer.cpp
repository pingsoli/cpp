/*
 * async timer
 */
#include <iostream>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void print(const boost::system::error_code& ec)
{
  std::cout << "Hello ,world!" << std::endl;
}

int main(int argc, char** argv)
{
  boost::asio::io_context io;

  boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
  t.async_wait(&print);  // Register a callback

  std::cout << "start to executing\n";

  // It's important to remember to give io_service some work to do before
  // calling the io_service.run().
  io.run();  // blocking to wait the print callback function to execute,
             // if no works to do, io.run() will return immediately,
             // so, it is going to quit the main function.

  std::cout << "main function\n";
  return 0;
}
