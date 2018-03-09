#ifndef _DATE_H__
#define _DATE_H__

#include <string>

class Date
{
public:
  Date(int year = 1997, int month = 12, int day = 30);

  int year() const;
  int month() const;
  int day() const;

  void setYear(int year);
  void setMonth(int month);
  void setDay(int day);

  std::string to_string() const;

private:
  int year_, month_, day_;
};

#endif // _DATE_H__
