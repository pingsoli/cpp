///////////////////////////////////////////////////////////////////////////////
//
// Item 13: Use objects to manage resources.
//
// auto_ptr, shared_ptr
//
// auto_ptr is deprecated since c++11 and removed from c++17, so don't use it.
//
// 1) To prevent resource leaks, use RAII objects that require resources in
// their constructors and release themm in their destructors.
//
// 2) Two commonly useful RAII classes are tr1::shared_ptr and auto_ptr.
// tr1::shared_ptr is usually the better choice, because its behavior when
// copied is intuitive. Copying an auto_ptr sets it to null.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// Why not use auto_ptr ?
//
// class X
// {
// };
//
// std::vector<std::auto_ptr<X> > vecX;
// vecX.push_back(new X);
//
// std::auto_ptr<X> pX = vecX[0];  // vecX[0] is assigned NULL.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <memory>

class Investment
{
public:
  Investment(const std::string& name, double price)
    : transaction_name_{name}, price_{price}
  { }

private:
  std::string transaction_name_;
  double      price_;
};

int main(int argc, char** argv)
{
  std::vector<std::shared_ptr<Investment>> inves_vec;
  inves_vec.emplace_back(new Investment("dkallfkaf", 129139132.0));
  inves_vec.emplace_back(new Investment("abcdef", 23824942.0));
  inves_vec.emplace_back(new Investment("what the fuck", 12309131.0));

  std::shared_ptr<Investment> pi = inves_vec[0];

  return 0;
}
