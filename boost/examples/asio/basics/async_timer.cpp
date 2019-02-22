// Async timer
//
// 1. async wait on timer
// 2. reset the timer when timeout
//
// Use timer to detect the timeout action when initiating a http request, if
// the request timeout and the timer will close the socket.

#include <iostream>
#include <thread>
#include <atomic>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// NOTE: Don't use equal expression for atomic assignments directly.
std::atomic_bool stop{0};

void do_something()
{
  unsigned int i = 0;
  while (!stop.load()) {
    std::cout << ++i << " seconds..." << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

int main(int argc, char** argv)
{

  {
    // boost::asio::io_context io;
    // boost::asio::deadline_timer timer(io, boost::posix_time::seconds(3));
    //
    // auto timer_timeout_func = [&timer] (const boost::system::error_code& [>ec<]) {
    //   std::cout << "Tiemr is timeout !" << '\n';
    //   // stop = 1;
    // };
    //
    // // Register a callback, when timer timeouts, the callback will be invoked.
    // timer.async_wait(timer_timeout_func);
    //
    // // Run the async handler on another thread, instead main thread.
    // std::thread worker_thread([&io] () { io.run(); });
    //
    // // // It's important to remember to give io_service some work to do before
    // // // calling the io_service.run().
    // // io.run();  // blocking to wait the print callback function to execute,
    // //            // if no works to do, io.run() will return immediately,
    // //            // so, it is going to quit the main function.
    //
    // do_something(); // when do something, the timer may be timeout.
    // worker_thread.join();
  }

  {
    // request timeout and the timer will detect and return
    namespace asio = boost::asio;
    asio::io_service io;

    // make the deadline_timer be a normal async job
    asio::deadline_timer request_work(io, boost::posix_time::seconds(1)); // normal request
    asio::deadline_timer timer(io, boost::posix_time::seconds(3)); // timer

    auto async_wait_func = [&timer] (boost::system::error_code ec) {
      if (timer.expires_at() >= boost::asio::deadline_timer::traits_type::now()) {
        // do nothing when request is finished
        std::cout << "Request is finished" << '\n';
      } else {
        // timeout and print message
        std::cout << "Request is timeout" << '\n';
        // close the socket
      }
    };

    auto initiate_connect = [&timer] (boost::system::error_code ec) {
      // do something
      timer.expires_at(boost::posix_time::pos_infin); // let timer expire now
      std::cout << "connect finished" << '\n';
    };

    timer.async_wait(async_wait_func); // set the timer
    request_work.async_wait(initiate_connect); // start request

    std::cout << "Main thread" << '\n';

    io.run();
  }

  return 0;
}
