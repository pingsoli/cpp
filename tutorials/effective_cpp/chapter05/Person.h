#ifndef _PERSON_H__
#define _PERSON_H__

#include <string>
#include <memory>

class PersonImpl;
class Date;

class Person
{
public:
  Person(const std::string& name, const Date& birthday,
         const std::string& address);

  std::string name() const;
  std::string birth_date() const;
  std::string address() const;

private:
  std::shared_ptr<PersonImpl> pImpl;
};

#endif // _PERSON_H__
