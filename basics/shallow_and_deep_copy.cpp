////////////////////////////////////////////////////////////////////////////////
// shallow and deep copy
// look down the following two examples.
// the first one is non dynamically allocated memory version.
// the second one is dynamically allocated memory version.
//
// summary:
// 1) the default copy constructor and default assignment operators do shallow
// copies, which is fine for classes that contain no dynamically allocated variables.
// 2) Classes with dynamically allocated variables need to have a copy constructor
// and assignment operator that do a deep copy.
// 3) Favor using classes in the standard library over doing your own memory management.
// such as std::string and std::vector.
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cassert>
#include <cstring>

// it's ok when there is no dynamically allocated memory.
// default assignment operator
class Fraction
{
public:
  // Default constructor
  Fraction(int numerator = 0, int denominator = 1) :
    m_numerator(numerator), m_denominator(denominator)
  {
    assert(denominator != 0);
  }

  // copy constructor
  Fraction(const Fraction& other) :
    m_numerator(other.m_numerator), m_denominator(other.m_denominator)
  {}

  // A better implementation of operator=
  Fraction& operator=(const Fraction& rhs) {
    // self-assignment guard
    if (this == &rhs)
      return *this;

    // do the copy
    m_numerator = rhs.m_numerator;
    m_denominator = rhs.m_denominator;

    // return the existing object so we can chain this operator.
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& out, const Fraction& f);

private:
  int m_numerator;
  int m_denominator;
};

std::ostream& operator<<(std::ostream& out, const Fraction& f)
{
  out << f.m_numerator << " / " << f.m_denominator;
  return out;
}

// now we handle the dynamically allocated memory.
class MyString
{
public:
  MyString(const char* source = "")
  {
    assert(source); // make sure source isn't the null string.

    m_length = strlen(source) + 1;
    m_data = new char[m_length];

    for (int i = 0; i < m_length; ++i)
      m_data[i] = source[i];

    m_data[m_length] = '\0';
  }

  // what will happen ? It's very dangerous.
  // this is shallow  copy, the destructor will free the data allocated from heap.
  //
  // MyString(const MyString& other) :
  //   m_length(other.m_length), m_data(other.m_data)
  // {}

  // deep copy, copy data totally, not make the pointer point to the same place.
  MyString(const MyString& other) {
    m_length = other.m_length;

    if (other.m_data)
    {
      m_data = new char[m_length];

      // do the copy
      for (int i = 0; i < m_length; ++i)
        m_data[i] = other.m_data[i];
    }
    else
      m_data = nullptr;
  }

  MyString& operator=(const MyString& rhs) {
    if (this == &rhs)
      return *this;

    // free the origin memory
    delete[] m_data;

    m_length = rhs.m_length;

    if (rhs.m_data)
    {
      m_data = new char[m_length];

      for (int i = 0; i < m_length; ++i)
        m_data[i] = rhs.m_data[i];
    }
    else
      m_data = nullptr;

    return *this;
  }

  char* getString() const { return m_data; }
  int getLength() const { return m_length; }

  ~MyString() {
    delete[] m_data;
  }

private:
  char *m_data;
  int m_length;
};

int main(int argc, char *argv[])
{
  MyString hello("hello world");
  {
    MyString copy = hello; // use copy constructor
  }

  std::cout << hello.getString() << '\n'; // this will have undefined behavior.

  return 0;
}
