#include "Date.h"
#include <sstream>

Date::Date(int year, int month, int day)
  : year_{year}, month_{month}, day_{day}
{
}

int Date::year() const
{
  return year_;
}

int Date::month() const
{
  return month_;
}

int Date::day() const
{
  return day_;
}

void Date::setYear(int year)
{
  year_ = year;
}

void Date::setMonth(int month)
{
  month_ = month;
}

void Date::setDay(int day)
{
  day_ = day;
}

std::string Date::to_string() const
{
  std::ostringstream oss;
  oss << year_ << '/' << month_ << '/' << day_;
  return oss.str();
}
