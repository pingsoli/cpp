/*
 * Instrusive VS. Non-Instrusive
 *
 * Instrusive:
 *   inner template function of a class
 *
 * Non-Instrusive:
 *   outside template function
 *
 * Summary:
 *   instrusive    : member variables are private.
 *   non-instrusive: member varibbles are public.
 */
#include <fstream>
#include <iostream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

// Instrusive version
class gps_position
{
private:
// Instrusive version
//  friend class boost::serialization::access;
//  template<class Archive>
//  void serialize(Archive & ar, const unsigned int version)
//  {
//    ar & degrees & minutes & seconds;
//  }

  // Non-instrusive version
  // So, if out member variable is private, we have to add the following code.
  // and implement in the outside.
  friend class boost::serialization::access;
  template <typename Archive>
  friend void serialize(Archive & ar, gps_position& g, const unsigned int ver);

  int   degrees;
  int   minutes;
  float seconds;

public:
  gps_position() = default;
  gps_position(int d, int m, float s) :
    degrees{d}, minutes{m}, seconds{s}
  {}

  void print()
  {
    std::cout << degrees << " " << minutes << " " << seconds << '\n';
  }
};

/*
 * What do you think of the two version ?
 * I'll do use instrusive if I member variable is private, or use
 * non-instrusive version.
 */
template <typename Archive>
void serialize(Archive &ar, gps_position& g, const unsigned int ver)
{
  ar & g.degrees;
  ar & g.minutes;
  ar & g.seconds;
}

int main(int argc, char** argv)
{
  // create and open a character archive for output
  std::ofstream ofs("filename");

  const gps_position g(35, 59, 24.567f);
  // save data to archive
  {
    boost::archive::text_oarchive oa(ofs);

    // write class instance to archive
    oa << g;
    // archive and stream closed when destructors are called
  }

  gps_position newg;
  {
    std::ifstream ifs{"filename"};
    boost::archive::text_iarchive ia{ifs};
    ia >> newg;

    newg.print();
  }

  return 0;
}
