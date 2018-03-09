#include "Person.h"
#include "PersonImpl.h"
#include "Date.h"

Person::Person(const std::string& name, const Date& birthday,
    const std::string& address)
  : pImpl{std::make_shared<PersonImpl>(name, birthday, address)}
{
}

std::string Person::name() const
{
  return pImpl->name();
}

std::string Person::birth_date() const
{
  return pImpl->birth_date();
}

std::string Person::address() const
{
  return pImpl->address();
}
