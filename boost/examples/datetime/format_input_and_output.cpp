#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>
#include <locale>

int main(int argc, char *argv[])
{
  using namespace boost::gregorian;

  {
    // format the output of date time.
    date d{2014, 5, 12};
    date_facet *df = new date_facet{"%A %d %B %Y"};
    // Monday 12 May 2014

    std::cout.imbue(std::locale{std::cout.getloc(), df});
    std::cout << d << '\n';
  }

  {
    // Change names of weekdays and months.
    try {
      std::string months[12]{"一月", "二月", "三月", "四月", "五月", "六月",
        "七月", "八月", "九月", "十月", "十一月", "十二月"};

      std::string weekdays[7]{"周日", "周一", "周二", "周三", "周四",
        "周五", "周六"};

      date d{2014, 5, 12};
      date_facet *df = new date_facet{"%A, %d. %B %Y"};
      df->long_month_names(std::vector<std::string>{months, months + 12});
      df->long_weekday_names(std::vector<std::string>{weekdays, weekdays + 7});

      std::cout.imbue(std::locale{std::cout.getloc(), df});
      std::cout << d << '\n';
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }

  return 0;
}
