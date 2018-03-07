///////////////////////////////////////////////////////////////////////////////
//
// Item 20: Prefer pass-by-reference-to-const to pass-by-value
//
// Passing parameters by reference also avoids the slicing problem.
//
// Slicing problem ?
// when a derived class object is passed (by value) as a base class object,
// the base class copy constructors is called, and the specialized features
// that make the object behave like a derived class object are "slice off".
//
// 1) Prefer pass-by-reference-to-const over pass-by-value. It's typically
// more efficient and it avoids the slicing problem.
//
// 2) The rule doesn't apply to built-in types and STL iterator and function
// object types. For them, pass-by-value is usually appropriate.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

class Person
{
public:
  Person(const std::string& name, const std::string& address)
    : name_{name}, address_{address}
  {
    std::cout << "Person constructor" << std::endl;
  }

  virtual ~Person()
  {
    std::cout << "Person destructor" << std::endl;
  }

  Person(const Person& p)
    : name_{p.name_},
      address_{p.address_}
  {
    std::cout << "Person copy constructor" << std::endl;
  }

private:
  std::string name_;
  std::string address_;
};

class Student : public Person
{
public:
  Student(const std::string& name, const std::string& address,
      const std::string& school_name, const std::string& school_address)
    : Person(name, address),
      school_name_{school_name},
      school_address_{school_address}
  {
    std::cout << "Student constructor" << std::endl;
  }

  ~Student()
  {
    std::cout << "Student destructor" << std::endl;
  }

  Student(const Student& s)
    : Person(s),
      school_name_{s.school_name_},
      school_address_{s.school_name_}
  {
    std::cout << "Student copy constructor" << std::endl;
  }

private:
  std::string school_name_;
  std::string school_address_;
};

// swallow copy Vs. deep copy ?
//
// call stack
// validateStudent
// -> Person copy constructor
// -> Student copy constructor
// -> Student destructor
// -> Person destructor
// bool validateStudent(Student s)
// {
//   std::cout << "Validate student ...." << std::endl;
//   return true;
// }

bool validateStudent(const Student& s)
{
  std::cout << "validate student ..." << std::endl;
  return true;
}

int main(int argc, char** argv)
{
  Student s("pingsoli", "Lord", "www", "www.");
  validateStudent(s);

  return 0;
}
