#include <iostream>
#include <chrono>
#include <thread>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "date.h" // output time_point for ostream

using namespace boost;
using namespace std::chrono;

// helper function - it's a completion handler
void timer_expired(std::string id) {
  std::cout << system_clock::now()
    << " [" << std::this_thread::get_id() << "] " << id << " enter\n";

  std::this_thread::sleep_for(std::chrono::seconds(2));

  std::cout << system_clock::now()
    << " [" << std::this_thread::get_id() << "] " << id << " leave\n";
}

int main(int argc, char* argv[])
{
  {
    // now, we have proactor, it's bulter. he will dispatch the completion
    // handler.
    asio::io_service service;

    // we have a timer, it's a task.
    asio::deadline_timer timer(service, posix_time::seconds(5));

    // after 5 seconds, the completion handler will be called.
    timer.async_wait([] (auto ... vn) {
        std::cout << system_clock::now()
        << ": timer expired.\n";
        });

    std::cout << system_clock::now() << ": calling run\n";

    service.run(); // expect there is work to do, if no work, run() will return.

    // this is the end of main program.
    std::cout << system_clock::now() << ": done.\n";
  }

  {
    // // only one thread
    // // watch two timer timeout events, we have two async oerations
    // // if the timers are both timeout, the completion handler will be called.
    // asio::io_service service;
    //
    // asio::deadline_timer timer1(service, posix_time::seconds(2));
    // asio::deadline_timer timer2(service, posix_time::seconds(2));
    //
    // timer1.async_wait([] (auto ... vn) { timer_expired("timer1"); });
    // timer2.async_wait([] (auto ... vn) { timer_expired("timer2"); });
    //
    // std::thread bulter([&] { service.run(); });
    // bulter.join();
    // std::cout << "done\n";
  }

  {
    // // what about two threads ? concurrency.
    // // the completion handler may be executed on different thread.
    // // the output will be unordered.
    // asio::io_service service;
    //
    // asio::deadline_timer timer1(service, posix_time::seconds(2));
    // asio::deadline_timer timer2(service, posix_time::seconds(2));
    //
    // timer1.async_wait([] (auto ... vn) { timer_expired("timer1"); });
    // timer2.async_wait([] (auto ... vn) { timer_expired("timer2"); });
    //
    // std::thread ta([&] { service.run(); });
    // std::thread tb([&] { service.run(); });
    //
    // ta.join();
    // tb.join();
    //
    // std::cout << "done\n";
  }

  {
    // asio::io_service service;
    // asio::io_service::strand strand(service);
    //
    // asio::deadline_timer timer1(service, posix_time::seconds(2));
    // asio::deadline_timer timer2(service, posix_time::seconds(2));
    // asio::deadline_timer timer3(service, posix_time::seconds(2));
    //
    // // All the completion handlers is in order.
    // timer1.async_wait(
    //     strand.wrap([] (auto ... vn) { timer_expired("timer1"); }));
    // timer2.async_wait(
    //     strand.wrap([] (auto ... vn) { timer_expired("timer2"); }));
    // // timer3.async_wait(
    // //     strand.wrap([] (auto ... vn) { timer_expired("timer3"); }));
    //
    // // we have an exception, timer3 is not in strand.
    // timer3.async_wait([] (auto ... vn) { timer_expired("timer3"); });
    //
    // std::thread ta([&] { service.run(); });
    // std::thread tb([&] { service.run(); });
    //
    // ta.join();
    // tb.join();
    //
    // std::cout << "done\n";
  }

  return 0;
}
