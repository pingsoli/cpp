#include <boost/circular_buffer.hpp>

int main(int argc, char *argv[])
{
  // create a circular buffer with a capacity for 3 integers.
  boost::circular_buffer<int> cb(3);

  // insert three elements into the buffer
  cb.push_back(1);
  cb.push_back(2);
  cb.push_back(3);

  int a = cb[0];
  int b = cb[1];
  int c = cb[2];

  cb.push_back(4);
  cb.push_back(5);

  a = cb[0];
  b = cb[1];
  c = cb[2];

  cb.pop_back();
  cb.pop_front();

  return 0;
}
