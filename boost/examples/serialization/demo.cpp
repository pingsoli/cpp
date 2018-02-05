/*
 * Mutiple bus stops, bus routes and schedules.
 *
 * There are different kind of bus stops, bus stops in general will multiple
 * trips on the same route.
 */
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>

class gps_position
{
private:
  friend std::ostream & operator<<(std::ostream& os, const gps_position &gp);
  friend class boost::serialization::access;

  int   degrees;
  int   minutes;
  float seconds;

  template <typename Archive>
  void serialize(Archive & ar, const unsigned int /* file_version */) {
    ar & degrees & minutes & seconds;
  }

public:
  gps_position() {}
  gps_position(int d, int m, int s) :
    degrees(d), minutes(m), seconds(s)
  {}
};

std::ostream & operator<<(std::ostream& os, const gps_position& gp)
{
  return os << ' ' << gp.degrees << (unsigned char)186
            << gp.minutes << '\'' << gp.seconds << '"';
}

class bus_stop
{
private:
  friend class boost::serialization::access;
  friend std::ostream & operator<<(std::ostream& os, const bus_stop& bs);
  virtual std::string description() const = 0;

  gps_position latitude;
  gps_position longtitude;

  template <typename Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & latitude;
    ar & longtitude;
  }

protected:
  bus_stop(const gps_position & _lat, const gps_position & _long) :
    latitude{_lat}, longtitude{_long}
  {}

public:
  bus_stop() {}
  virtual ~bus_stop() {}
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(bus_stop)

std::ostream & operator<<(std::ostream& os, const bus_stop &bs)
{
  return os << bs.latitude << bs.longtitude << ' ' << bs.description();
}

class bus_stop_corner : public bus_stop
{
private:
  friend class boost::serialization::access;
  std::string street1;
  std::string street2;

  virtual std::string description() const
  {
    return street1 + " and " + street2;
  }

  template <typename Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    // Why need this ?
    ar & boost::serialization::base_object<bus_stop>(*this);
    ar & street1 & street2;
  }

public:
  bus_stop_corner() {}
  bus_stop_corner(const gps_position & _lat, const gps_position & _long,
    std::string const & _s1, std::string const & _s2
  ) :
    bus_stop(_lat, _long), street1{_s1}, street2{_s2}
  {
  }
};

class bus_stop_destination : public bus_stop
{
private:
  friend class boost::serialization::access;
  std::string name;

  virtual std::string description() const
  {
    return name;
  }

  template <typename Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & boost::serialization::base_object<bus_stop>(*this) & name;
  }

public:
  bus_stop_destination() {}
  bus_stop_destination(const gps_position& _lat,
    const gps_position& _long,
    std::string const& _name
  ) :
    bus_stop(_lat, _long), name(_name)
  {
  }
};

class bus_route
{
private:
  friend class boost::serialization::access;
  friend std::ostream & operator<<(std::ostream& os, const bus_route & br);

  typedef bus_stop * bus_stop_pointer;
  std::list<bus_stop_pointer> stops;

  template <typename Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    // What does this do ?
    ar.register_type(static_cast<bus_stop_corner *>(NULL));
    ar.register_type(static_cast<bus_stop_destination *>(NULL));

    ar & stops;
  }

public:
  bus_route() {}
  void append(bus_stop *_bs)
  {
    stops.insert(stops.end(), _bs);
  }
};

std::ostream& operator<<(std::ostream& os, const bus_route& br)
{
  std::list<bus_stop*>::const_iterator it;

  for (it = br.stops.begin(); it != br.stops.end(); ++it) {
    os << '\n' << std::hex << "0x" << *it << std::dec << ' ' << **it;
  }
  return os;
}

class bus_schedule
{
public:
  struct trip_info
  {
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int file_version)
    {
      if (file_version >= 2)
        ar & driver;

      ar & hour & minute;
    }

    int hour;
    int minute;
    std::string driver;

    trip_info() {}
    trip_info(int _h, int _m, const std::string &_d) :
      hour{_h}, minute{_m}, driver{_d}
    {}
  };

private:
  friend class boost::serialization::access;
  friend std::ostream& operator<<(std::ostream& os, const bus_schedule &bs);
  friend std::ostream& operator<<(std::ostream& os,
                                  const bus_schedule::trip_info &ti);

  std::list<std::pair<trip_info, bus_route *>> schedule;
  template <typename Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar & schedule;
  }

public:
  void append(const std::string& _d, int _h, int _m, bus_route *_br)
  {
    schedule.insert(schedule.end(), std::make_pair(trip_info(_h, _m, _d), _br));
  }

  bus_schedule() {}
};

BOOST_CLASS_VERSION(bus_schedule::trip_info, 2)


std::ostream& operator<<(std::ostream& os, const bus_schedule::trip_info& ti)
{
  return os << '\n' << ti.hour << ":" << ti.minute << ' ' << ti.driver << ' ';
}

std::ostream& operator<<(std::ostream& os, const bus_schedule& bs)
{
  std::list<std::pair<bus_schedule::trip_info, bus_route*>>::const_iterator it;
  for (it = bs.schedule.begin(); it != bs.schedule.end(); ++it) {
    os << it->first << *(it->second);
  }
  return os;
}

void save_schedule(const bus_schedule &s, const char* filename)
{
  std::ofstream ofs(filename);
  boost::archive::text_oarchive oa(ofs);
  oa << s;
}

void restore_schedule(bus_schedule &s, const char *filename)
{
  std::ifstream ifs(filename);
  boost::archive::text_iarchive ia(ifs);
  ia >> s;
}
int main(int argc, char** argv)
{
  // make the schedule
  bus_schedule original_schedule;

  // fill in the data
  // make a new stops
  bus_stop *bs0 = new bus_stop_corner(
    gps_position(34, 135, 53.560f),
    gps_position(134, 22, 78.30f),
    "24th Street", "10th Avenue"
  );

  bus_stop *bs1 = new bus_stop_corner(
    gps_position(35, 137, 23.456f),
    gps_position(133, 35, 54.12f),
    "State street", "Cathedral Vista Lane"
  );

  bus_stop *bs2 = new bus_stop_destination(
    gps_position(35, 136, 15.456f),
    gps_position(133, 32, 15.456f),
    "White House"
  );

  bus_stop *bs3 = new bus_stop_destination(
    gps_position(35, 134, 48.789f),
    gps_position(133, 32, 16.230f),
    "Licoln Memorial"
  );

  // make a route
  bus_route route0;
  route0.append(bs0);
  route0.append(bs1);
  route0.append(bs2);

  original_schedule.append("bob", 6, 24,    &route0);
  original_schedule.append("bob", 9, 57,    &route0);
  original_schedule.append("alice", 11, 02, &route0);

  // make a route
  bus_route route1;
  route1.append(bs3);
  route1.append(bs2);
  route1.append(bs1);

  // add trips to schedule
  original_schedule.append("ted", 7, 17,    &route1);
  original_schedule.append("ted", 9, 38,    &route1);
  original_schedule.append("alice", 11, 47, &route1);

  // display the complete schedule
  std::cout << "original schedule";
  std::cout << original_schedule;

  std::string filename(boost::archive::tmpdir());
  filename += "/demofile.txt";

  // save the schedule
  save_schedule(original_schedule, filename.c_str());

  //  ... some time later
  //  make a new schedule
  bus_schedule new_schedule;

  restore_schedule(new_schedule, filename.c_str());

  // and display
  std::cout << "\n\nrestored scheduled";
  std::cout << new_schedule;
  std::cout << '\n';

  delete bs0;
  delete bs1;
  delete bs2;
  delete bs3;

  return 0;
}
