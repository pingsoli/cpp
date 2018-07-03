#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>

using namespace boost::posix_time;
using namespace boost::gregorian;

int main(int argc, char *argv[])
{
  {
    ptime pt{date{2014, 5, 12}, time_duration{12, 0, 0}};
    date d = pt.date();
    std::cout << d << '\n';

    time_duration td = pt.time_of_day();
    std::cout << td << '\n';
  }

  {
    ptime pt = second_clock::universal_time();
    std::cout << pt.date() << '\n';
    std::cout << pt.time_of_day() << '\n';

    pt = from_iso_string("20140512T120000");
    std::cout << pt.date() << '\n';
    std::cout << pt.time_of_day() << '\n';
  }

  {
    time_duration td{16, 30, 0};
    std::cout << td.hours() << '\n';
    std::cout << td.minutes() << '\n';
    std::cout << td.seconds() << '\n';
    std::cout << td.total_seconds() << '\n';
  }

  return 0;
}
