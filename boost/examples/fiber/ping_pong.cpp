/*
 * What is buffered channel?
 * Buffered channel(MPMC queue) suitable to synchonize fibers.
 */
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include <boost/fiber/all.hpp>

int main(int argc, char** argv)
{
  using channel_t = boost::fibers::buffered_channel<std::string>;

  try {
    // specify channel's capacity
    channel_t chan1{ 2 }, chan2{ 2 };

    boost::fibers::fiber fping([&chan1, &chan2] {
      chan1.push("ping");
      std::cout << chan2.value_pop() << '\n';
      chan1.push("ping");
      std::cout << chan2.value_pop() << '\n';
      chan1.push("ping");
      std::cout << chan2.value_pop() << '\n';
    });

    boost::fibers::fiber fpong([&chan1, &chan2] {
      std::cout << chan1.value_pop() << '\n';
      chan2.push("pong");
      std::cout << chan1.value_pop() << '\n';
      chan2.push("pong");
      std::cout << chan1.value_pop() << '\n';
      chan2.push("pong");
    });

    fping.join();
    fpong.join();

    std::cout << "\nDone." << std::endl;
    return EXIT_SUCCESS;
  } catch (std::exception const& e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "unhandled exception" << std::endl;
  }

  return EXIT_FAILURE;
}
