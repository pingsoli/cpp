////////////////////////////////////////////////////////////////////////////////
// Virtual Function and Virtual Table
//
// on x64 system, the pointer size is 8 bytes.
//
// C++ compiler inserts a pointer v_ptr called as virtual table pointer.
// Compiler also creates a table for that class called as virtual table k
// nown as vtable for the class. The table is created compile time v_ptr holds
// the address of v_table of the corresponding class. vtable is a array of
// function pointers pointing to a virtual function.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

class Vehicle {
public:
  virtual void apply_break() {
    std::cout << "Vehicle break" << std::endl;
  }
  virtual void apply_horn() {
    std::cout << "Vehicle horn" << std::endl;
  }
};

class Car : public Vehicle {
public:
  void apply_horn () {
    std::cout << "Car horn" << std::endl;
  }
};

class Trunk : public Vehicle {
public:
  void apply_break() {
    std::cout << "Trunk break" << std::endl;
  }
};

int main(int argc, char** argv)
{
  std::cout << "Vehicle size: " << sizeof(Vehicle) << std::endl;  // 8
  std::cout << "Turnk size:   " << sizeof(Trunk) << std::endl;    // 8
  std::cout << "Car size:     " << sizeof(Car) << std::endl;      // 8

  Vehicle *trunk = new Trunk();
  trunk->apply_break();  // Trunk break
  trunk->apply_horn();   // Vehicle break

  Vehicle *car = new Car();
  car->apply_break();    // Vehicle break
  car->apply_horn();     // Car horn

  return 0;
}
