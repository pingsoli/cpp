///////////////////////////////////////////////////////////////////////////////
//
// Item 07: Declare destructors virtual in polymorphic base classes.
//
// 1) Polymorphic base class should declare virtual destructors. If a class has
// any virtual functions, it should have a virtual destructor.
//
// 2) Classes not designed to be base class or not designed to be used
// polymorphically should not declare virtual destrutors.
//
// 3) Use smart pointer whenever possible.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>
#include <string>

class TimeKeeper
{
public:
  TimeKeeper(int hour, int minute, int second)
    : hour_{hour},
      minute_{minute},
      second_{second}
  { }

  virtual ~TimeKeeper() {
    std::cout << "TimeKeeper destructor" << std::endl;
  }

private:
  int hour_, minute_, second_;
};

class AtomicClock : public TimeKeeper
{
public:
  AtomicClock(const std::string& name, int hour, int minute, int second)
    : TimeKeeper(hour, minute, second),
      name_{name}
  { }

  ~AtomicClock() {
    std::cout << "AtomicClock destructor" << std::endl;
  }

private:
  std::string name_;
};

class WaterClock : public TimeKeeper
{
public:
  WaterClock(const std::string& version, int hour, int minute, int second)
    : TimeKeeper(hour, minute, second),
      version_{version}
  { }

  ~WaterClock() {
    std::cout << "WaterClock destructor" << std::endl;
  }

private:
  std::string version_;
};

class WristWatch : public TimeKeeper
{
public:
  WristWatch(float temperature, int hour, int minute, int second)
    : TimeKeeper(hour, minute, second),
      temperature_{temperature}
  {
  }

  ~WristWatch()
  {
    std::cout << "WristWatch destructor" << std::endl;
  }

private:
  float temperature_;
};

// Smart pointer version, release resource automatically and cleanly
// no matter TimeKeeper's destructor is virutal.
std::shared_ptr<TimeKeeper> getTimeKeeper(int flag)
{
  switch (flag)
  {
  case 1:
    return std::shared_ptr<TimeKeeper>(new AtomicClock("atomic", 12, 10, 9));
  case 2:
    return std::shared_ptr<TimeKeeper>(new WaterClock("1.1.0", 12, 10, 9));
  case 3:
    return std::shared_ptr<TimeKeeper>(new WristWatch(27.0, 12, 10, 9));
  }

  return std::shared_ptr<TimeKeeper>(new AtomicClock("atomic", 12, 10, 9));
}

// Raw pointer version, won't clean the resouce completely if TimeKeeper is
// non-virtual.
TimeKeeper* getTimeKeeperPtr(int flag)
{
  switch (flag)
  {
  case 1:
    return new AtomicClock("atomic", 12, 10, 9);
  case 2:
    return new WaterClock("1.1.1", 12, 10, 9);
  case 3:
    return new WristWatch(27.0, 12, 10, 9);
  }

  return new AtomicClock("atomic", 12, 10, 9);
}

class PointWithoutVirtual
{
public:
  PointWithoutVirtual(int x, int y)
    : x_{x}, y_{y}
  {
  }

  ~PointWithoutVirtual() {}
private:
  int x_, y_;
};

// class Point has a virtual destructor
class Point
{
public:
  Point(int x, int y)
    : x_{x}, y_{y}
  {}

  virtual ~Point() {}
private:
  int x_, y_;
};

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////
  //
  // Use smart pointer to manage object

  std::shared_ptr<TimeKeeper> ptk = getTimeKeeper(1);

  // no matter the base class's destructor is virtual or not, smart point will
  // release the resource completely.
  // so the output always like this:
  // AtomicClock destructor
  // TimeKeeper destructor

  /////////////////////////////////////////////////////////////////////////////
  //
  // Use raw pointer

  TimeKeeper* ptk1 = getTimeKeeperPtr(1);

  // Don't forget to release the pointer
  delete ptk1;

  // base calss TimeKeeper has no virtual destructor, the output like this:
  // TimeKeeper destructor

  // base class TimeKeeper has virtual destructor, the output like this:
  // AtomicClock destructor
  // TimeKeeper destructor

  /////////////////////////////////////////////////////////////////////////////
  //
  // virutal function cost ? more space.
  // vptr(virtual table pointer) and vtbl(virtual table)

  // int is 4 bytes, two member variables cost 8 bytes.
  std::cout << "the size of PointWithoutVirtual: "
    << sizeof(PointWithoutVirtual) << std::endl;
  // the size of PointWithoutVirtual: 8

  // pointer is 8 bytes in 64-machines.
  // so, the total size is: two integers + pointer = 16 bytes.
  std::cout << "the size of Point: " << sizeof(Point) << std::endl;
  // the size of Point: 16
  //
  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
