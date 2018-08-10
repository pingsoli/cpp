#pragma once

#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdio>

std::ostream& operator<<(std::ostream& os,
    std::chrono::system_clock::time_point tp)
{
  using namespace std;
  using namespace std::chrono;
  auto duration = tp.time_since_epoch();

  duration -= duration_cast<seconds>(duration);
  time_t tt = system_clock::to_time_t(tp);
  tm t{*localtime(&tt)};

  char buf[64] = {0};
  sprintf(buf, "[%04u-%02u-%02u %02u:%02u:%02u.%03u]",
      t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
      t.tm_hour, t.tm_min, t.tm_sec,
      static_cast<unsigned>(duration / milliseconds(1)));

  return (os << buf);
}
