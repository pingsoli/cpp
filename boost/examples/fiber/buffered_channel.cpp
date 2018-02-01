/*
 * What is the capacity of buffered_channel ?
 * It's a container, the capacity decide the buffer can contain how many
 * elements.
 *
 * So, capacity is arbitrary value ?
 * NO, my computer max size is 8, can't be bigger.
 *
 * Why? It depends on computer core number?
 * No answer.
 */
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include <boost/fiber/all.hpp>

typedef boost::fibers::buffered_channel<int> channel_t;

/*
 * The pop() and push() is same as most container, so, take is easy, and see
 * it as a sequence container.
 */
void send(channel_t& chan) {
  for (int i = 0; i < 5; ++i) {
    chan.push(i);
  }
  chan.close();
}

void recv(channel_t& chan) {
  int i;
  while (boost::fibers::channel_op_status::success == chan.pop(i)) {
    std::cout << "received " << i << std::endl;
  }
}

void one_channel() {
  channel_t chan { 8 };
  boost::fibers::fiber f1(std::bind(send, std::ref(chan)));
  boost::fibers::fiber f2(std::bind(recv, std::ref(chan)));

  f1.join();
  f2.join();
}

void foo(channel_t& chan) {
  chan.push(1);
  chan.push(1);
  chan.push(2);
  chan.push(3);
  chan.push(5);
  chan.push(8);
  chan.push(13);
  chan.close();
}

void bar(channel_t& chan) {
  for (unsigned int value : chan) {
    std::cout << value << " ";
  }

  std::cout << std::endl;
}

/* support range for */
void range_for() {
  channel_t chan { 4 };

//  boost::fibers::fiber f1(std::bind(foo, std::ref(chan)));
//  boost::fibers::fiber f2(std::bind(bar, std::ref(chan)));

  // partial function application
  // g(a, b) := f(a, 4, b)
  // auto g = bind(f, _1, 4, _2);
  //
  // same approach
  boost::fibers::fiber f1(foo, std::ref(chan));
  boost::fibers::fiber f2(bar, std::ref(chan));

  f1.join();
  f2.join();
}

int main(int argc, char **argv)
{
//  one_channel();
  range_for();
  return 0;
}
