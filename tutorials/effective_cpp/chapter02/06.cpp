///////////////////////////////////////////////////////////////////////////////
//
// Item 06: Explicitly disallow the use of compiler-generated functions you do
//          not want.
//
// To disallow functionality automatically provided by compilers, declare the
// corresponding member function private and give no implementations. Using
// a base class like Uncopyable is one way to do this.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

class HomeForSale
{
public:
  HomeForSale(const std::string& address, double price)
    : address_{address},
      price_{price}
  {
  }

  // C++11 features
  HomeForSale(const HomeForSale& )            = delete;
  HomeForSale& operator=(const HomeForSale& ) = delete;

private:
  std::string address_;
  double      price_;
};

class Uncopyable
{
protected:
  Uncopyable() {}
  ~Uncopyable() {}

private:
  Uncopyable(const Uncopyable&);
  Uncopyable& operator=(const Uncopyable&);
};

class NewHomeForSale : public Uncopyable
{
public:
  NewHomeForSale(const std::string& address, double price)
    : address_{address},
      price_{price}
  {
  }

private:
  std::string address_;
  double      price_;
};

int main(int argc, char** argv)
{
  HomeForSale h1("new york", 1200000);
//  HomeForSale h2(h1); // error, call deleted copy constructor

//  HomeForSale h2("cinna", 2392932); // error, call deleted copy assignment
//                                    // function.
//  h2 = h1;
//
//  HomeForSale h3 = h1;  // NOTE: invoke copy constructor not copy assignment
//                        // function.

  NewHomeForSale nh("haity", 128389);
//  NewHomeForSale nh1(nh);

  return 0;
}
