#include "PersonImpl.h"

PersonImpl::PersonImpl(const std::string& name, const Date& birth_date,
    const std::string& address)
  : name_{name}, birth_date_{birth_date}, address_{address}
{
}

std::string PersonImpl::name() const
{
  return name_;
}

std::string PersonImpl::birth_date() const
{
  return birth_date_.to_string();
}

std::string PersonImpl::address() const
{
  return address_;
}
