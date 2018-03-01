///////////////////////////////////////////////////////////////////////////////
//
// Item 4: Make sure that objects are initialized before they're used
//
// Things to remember:
// 1) Manually initialize objects of built-in type, because C++ only sometimes
//    initializes them itself.
//
// 2) In a constructor, prefer use of the member initialization list to
//    assignment inside the body of constructor. List data members in the
//    initialization list in the same order they're declared in the class.
//
// 3) Avoid initialization order problem across translation units by replacing
//    non-local static object with local static objects.
//
///////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <list>

class PhoneNumber
{
public:
  PhoneNumber(const std::string& phone)
    : phone_{phone}
  {
  }

  std::string phone() const
  {
    return phone_;
  }

private:
  std::string phone_;
};

class ABEntry
{
public:

  // Take care of the member initialization sequence
  // theName -> theAddress -> thePhones
  //
  // NOTE: following code is not initialization, is assignment.
  // ABEntry(const std::string& name, const std::string address,
  //     const std::list<PhoneNumber>& phones)
  // {
  //    theName = name;
  //    theAddress = address;
  //    thePhones = phones;
  //    numTimesConsulted = 0;
  // }
  ABEntry(const std::string& name, const std::string& address,
      const std::list<PhoneNumber>& phones)
    : theName{name},
      theAddress{address},
      thePhones{phones},
      numTimesConsulted{0}
  {
  }

  void print()
  {
    int i = 1;

    std::cout
      << "name: " << theName << '\n'
      << "address: " << theAddress << '\n'
      << "phones: \n";
    for (auto& p: thePhones)
      std::cout << "  Phone " << i++ << ": " << p.phone() << '\n';
  }

private:
  std::string theName;
  std::string theAddress;
  std::list<PhoneNumber> thePhones;
  int numTimesConsulted;
};

int main(int argc, char** argv)
{
  std::list<PhoneNumber> phones;
  phones.emplace_back("128383");
  phones.emplace_back("2834938");
  phones.emplace_back("182398193");

  ABEntry ab("pingsoli", "wuhan", phones);
  ab.print();

  return 0;
}
