////////////////////////////////////////////////////////////////////////////////
// Keep in mind:
// 1) the reference counter is managed atomatically but the pointer class access
// is not thread-safe.
// 2) Use shared_from_this() to return a shared pointer to *this. The class must
// derive from std::enable_shared_from_this.
// 3) Casting between pointer types can be done using
//   dynamic_pointer_cast,
//   static_pointer_cast,
//   reinterpret_pointer_cast.
// 4) shared_ptr might create cyclic dependencies and memory leaks when two
// pointers point to each other.
////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <iostream>

struct Person {
  Person(const std::string& name, int age) :
    name_(name), age_(age) {
    std::cout << "Person()" << '\n';
  }

  ~Person() {
    std::cout << "~Person()" << '\n';
  }

  std::string name_;
  int age_;
};

std::ostream& operator<<(std::ostream& os, const Person& p) {
  os << "name: " << p.name_ << "\nage: " << p.age_;
  return os;
}

// shared_ptr makes sure the destructor is called.
struct Base {
  Base() { std::cout << "Base constructor" << '\n';}
  // forget to add 'virtual'
  ~Base() { std::cout << "Base destructor" << '\n';}
};

struct Derived : public Base {
  Derived() { std::cout << "Derived constructor" << '\n';}
  ~Derived() { std::cout << "Derived destructor" << '\n';}
};

int main(int argc, char *argv[])
{
  {
    auto spi = std::make_shared<Person>("pingsoli", 50);

    // dereference shared pointer
    std::cout << *spi << '\n';

    // check the ref-count
    std::cout << "use count: " << spi.use_count() << '\n';

    // custom deleter
    auto deleter = [] (Person* p) {
      std::cout << "Delete" << '\n';
      delete p;
    };

    // don't use raw pointer to fulfill the shared ptr. It's bad.
    // use make_shared() or new inner the shared_ptr constructor.
    Person* pperson = new Person("pingsoli", 40);
    std::shared_ptr<Person> person(pperson, deleter);
  }

  {
    // if we forget to add 'virtual' keyword on destructor of base class, what
    // happened ? the constructor of derived class will be called ?
    auto pb = std::make_shared<Derived>();

    // when go outside, std::shared_ptr will call the Derived's destructor,
    // because std::shared_ptr remember the pointer type during construction.
    // if you say shared_ptr{ new Derived{} };
    // then shared_ptr will internally store a Derived*.

    // if we use new and delete.
    Base *b = new Derived();
    delete b; // the constructor of derived class will not invoked.
  }

  return 0;
}
