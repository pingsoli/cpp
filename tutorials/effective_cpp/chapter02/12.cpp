///////////////////////////////////////////////////////////////////////////////
//
// Item 12: Copy all parts of an object.
//
// 1) Copying functions should be sure to copy all of an object's data members
// and all of its base class parts.
//
// 2) Don't try to implement one of the copying functions in terms of the other
// Instead, put common functionality in a third function that both call.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

void logCall(const std::string& funcName)
{
  std::cout << funcName << " is calling" << std::endl;
}

class Date
{
public:
  Date(int hour = 0, int minute = 0, int second = 0)
    : hour_{hour}, minute_{minute}, second_{second}
  {}

private:
  int hour_, minute_, second_;
};

class Customer
{
public:
  Customer(const std::string name)
    : name_{name}
  {}

  Customer(const Customer& rhs)
    : name_{rhs.name_},
      last_transaction_{rhs.last_transaction_}
  {
    logCall("Customer copy constructor");
  }

  Customer& operator=(const Customer& rhs)
  {
    logCall("Customer copy assignment operator");
    name_ = rhs.name_;
    last_transaction_ = rhs.last_transaction_;
    return *this;
  }

private:
  std::string name_;
  Date        last_transaction_;
};

class PriorityCustomer : public Customer
{
public:
  PriorityCustomer(const std::string& name, int priority)
    : Customer(name),
      priority_{priority}
  {}

  PriorityCustomer(const PriorityCustomer& rhs)
    : Customer(rhs),
      priority_{rhs.priority_}
  {
    logCall("PriorityCustomer copy constructor");
  }

  PriorityCustomer& operator=(const PriorityCustomer& rhs)
  {
    logCall("PriorityCustomer copy assignment operator");
    Customer::operator=(rhs);
    priority_ = rhs.priority_;
    return *this;
  }

private:
  int priority_;
};

int main(int argc, char** argv)
{
  PriorityCustomer pc1("pingsoli", 0);
  PriorityCustomer pc2("ally", 20);

  pc2 = pc1;

  return 0;
}
