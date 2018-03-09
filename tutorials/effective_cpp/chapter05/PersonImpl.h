#ifndef _PERSONIMPL_H__
#define _PERSONIMPL_H__

#include <string>
#include "Date.h"

class PersonImpl
{
public:
  PersonImpl(const std::string& name, const Date& birth_date,
      const std::string& address);

  std::string name() const;
  std::string birth_date() const;
  std::string address() const;

private:
  std::string name_;
  Date birth_date_;
  std::string address_;
};

#endif // _PERSONIMPL_H__
