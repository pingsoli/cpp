////////////////////////////////////////////////////////////////////////////////
// gregorian calendar dates
////////////////////////////////////////////////////////////////////////////////
#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
  using namespace boost::gregorian;

  {
    date d{2017, 12, 20};
    std::cout << d.year() << '\n';  // 2017
    std::cout << d.month() << '\n'; // Dec
    std::cout << d.day() << '\n';   // 20
    std::cout << d.day_of_week() << '\n'; // Wed
    std::cout << d.day_of_year() << '\n'; // 354
  }

  {
    // UTC date
    date d1 = day_clock::universal_day();
    std::cout << d1.year() << '\n';
    std::cout << d1.month() << '\n';
    std::cout << d1.day() << '\n';
  }

  {
    // get date from a string
    date d = date_from_iso_string("20171230");
    std::cout << d.year() << '\n';
    std::cout << d.month() << '\n';
    std::cout << d.day() << '\n';
  }

  {
    // calculate date duration
    date d2{2014, 12, 31};
    date d3{2015, 1,  1};
    date_duration dd = d3 - d2;
    std::cout << dd.days() << '\n';
  }

  {
    date d4{2014, 1, 31};
    months ms{1};
    date d5 = d4 + ms;
    std::cout << d4 << '\n'; // 2014-Jan-31
    date d6 = d5 - ms;
    std::cout << d6 << '\n'; // 2014-Jan-31
  }

  {
    // date period
    date d1{2014, 1, 1};
    date d2{2014, 2, 28};
    date_period dp{d1, d2};
    date_duration dd = dp.length();
    std::cout << dd.days() << '\n'; // 58

    // test whether a period contains dates, [d1, d2)
    std::cout.setf(std::ios::boolalpha);
    std::cout << dp.contains(d1) << '\n'; // true
    std::cout << dp.contains(d2) << '\n'; // false
  }

  return 0;
}
