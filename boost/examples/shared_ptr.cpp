// Talking about Smart Pointer Parameter
// https://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/

#include <boost/smart_ptr/shared_ptr.hpp>
#include <iostream>
#include <memory>

struct Person
{
  std::string name;
  int age;
  std::string sex;

  Person(const std::string& name,
         int age,
         const std::string& sex)
    : name{name}, age{age}, sex{sex}
  {
  }

  void print() const
  {
    std::cout << name << " " << age << " "
              << sex << '\n';
  }
};

// shared_ptr is copy-constructed
void f(boost::shared_ptr<Person> p)
{
  // increate the reference count
  std::cout << p.use_count() << std::endl;

  // when escape the scope decrete reference count
}

// if p is null, we must check it before modify the object
void f(Person* p)
{
  if (p == nullptr) return;

  p->name = "test";
  p->age = 90;
  p->sex = "woman";
}

// knowing it won't be nullable object, so we want to change the object
void f(Person& p)
{
  p.name = "reference";
  p.age = 80;
  p.sex = "woman";
}

// won't change the p content
void f(const Person& p)
{
  p.print();
}

// advice
// 1) Don't pass a smart pointer as a function parameter unless you want
// to use or manipulate the smart pointer itself, such as share or
// transfer ownership.
// 2) Prefer passing objects by value, *, or &, not by smart pointer.

int main(int argc, char **argv)
{
  using namespace boost;

  shared_ptr<Person> p{ new Person{"pingsoli", 23, "man"} };

  // which is better? 
  // It depends.
  f(&(*p));  // f(Person* ), some kind ugly
  f(*p);     // f(Person& ), more elegant
  f(const_cast<const Person&>(*p));  // f(const Person& )

  return 0;
}
