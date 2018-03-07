///////////////////////////////////////////////////////////////////////////////
//
// Item 18: Make interfaces easy to use correctly and hard to use incorrectly.
//
// 1) Good interfaces are easy to use correctly and hard to use incorrectly.
// You should strive for the characteristics in all your interfaces.
//
// 2) Ways to facilitate correct use include consistency in interfaces and
// behavioral compatibility with built-in types.
//
// 3) Ways to prevente errors include creating new types, restricting
// operations on types, constraining object values, and eliminating client
// resource management responsibilities.
//
// 4) shared_ptr supports custom deletes. This prevents the cross-DLL problem,
// can be used to automatically unlock mutexes(See item14) etc.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

///////////////////////////////////////////////////////////////////////////////
//
// error-prone version

class Date
{
public:
  Date(int year, int month, int day)
    : year_{year}, month_{month}, day_{day}
  {}

  void print()
  {
    std::cout << year_ << '/' << month_ << '/' << day_ << std::endl;
  }

private:
  int year_, month_, day_;
};

///////////////////////////////////////////////////////////////////////////////
//
// non error prone version

struct Month {
  explicit Month(int month)
    : val{month} {}
  int val;
};

struct Day {
  explicit Day(int day)
    : val{day} {}
  int val;
};

struct Year {
  explicit Year(int year)
    : val{year} {}
  int val;
};

class DateNew {
public:
  DateNew(const Year& year, const Month& month, const Day& day)
    : year_{year}, month_{month}, day_{day}
  {}

  void print()
  {
    std::cout << year_.val << '/' << month_.val << '/' << day_.val << '\n';
  }

private:
  Year  year_;
  Month month_;
  Day   day_;
};

///////////////////////////////////////////////////////////////////////////////


int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////

  Date d(2017, 12, 30);
  d.print();

  // error-prone, in america, the date is formed by month/day/year.

  /////////////////////////////////////////////////////////////////////////////

  DateNew dn(Year(2017), Month(12), Day(30));
  dn.print();

  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
