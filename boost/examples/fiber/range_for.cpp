/*
 * fiber unbuffered channel
 *
 * synchonize fibers(running on same or different thread)
 * via synchronous message passing.
 *
 * A fiber waiting to consume an value will block until the value is produced.
 * If a fiber attempts to send a value through an unbuffered channel and no
 * fiber is waiting to receive the value, the channel will block the sending
 * fiber.
 */
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include <boost/fiber/all.hpp>

typedef boost::fibers::unbuffered_channel<unsigned int> channel_t;

void foo(channel_t& chan) {
  chan.push(1);
  chan.push(1);
  chan.push(2);
  chan.push(3);
  chan.push(5);
  chan.push(8);
  chan.push(12);

  chan.close();
}

void bar(channel_t& chan) {
  for (unsigned int value: chan) {
    std::cout << value << " ";
  }

  std::cout << std::endl;
}

int main(int argc, char ** argv)
{
  try {
    channel_t chan;

    boost::fibers::fiber f1(&foo, std::ref(chan));
    boost::fibers::fiber f2(&bar, std::ref(chan));

    f1.join();
    f2.join();

    std::cout << "Done." << std::endl;
  } catch (std::exception const & e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << "unhandled exception" << std::endl;
  }
  return 0;
}

// output:
// 1 1 2 3 5 8 12 
// Done.
