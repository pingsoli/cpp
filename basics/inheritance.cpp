////////////////////////////////////////////////////////////////////////////////
// the program discuss the base class own the operator= function
// it's will be ambigous, such as
// cat, and lizard class inherited from animal, if we don't disable operator= in
// Animal class, the compiler will generate one for us.
//
// *cat = *lizard; // it should be illegal.
//
// so we must disable operator= fucntion explicitly. such as:
// Animal& operator=(const Animal&) = delete;
//
////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <iostream>

class Animal {
public:
  Animal(const std::string& name) : name_(name) {};
  Animal& operator=(const Animal&) = delete;

protected:
  std::string name_;
};

class Lizard : public Animal {
public:
  Lizard(const std::string& name) : Animal(name) {}

  Lizard& operator=(const Lizard& other) {
    name_ = other.name_;
    return *this;
  }
};

class Cat : public Animal {
public:
  Cat(const std::string& name) : Animal(name) {}

  Cat& operator=(const Cat& other) {
    name_ = other.name_;
    return *this;
  }
};

int main(int argc, char *argv[])
{
  Lizard liz1("liz1");
  Cat cat1("cat1");

  Animal *pAnimal1 = &liz1;
  Animal *pAnimal2 = &cat1;

  // *pAnimal1 = *pAnimal2; // we delete the Animal& operator=(const Animal&) function.

  return 0;
}
