///////////////////////////////////////////////////////////////////////////////
//
// Item 09: Never call virtual functions during construction or destruction.
//
// Why ? What's the problem ?
// Don't call virtual functions during construction or destruction, because
// such calls will never go to a more derived class than that of the currently
// executing constructor or destructor.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

class Transaction
{
public:
  Transaction(double price)
    : price_{price}
  {
    /* do something */
    std::cout << "Transaction constructor" << std::endl;
    logTransaction();
  }

// call pure virtual function in constructor or destructor will get error
// message when linking.
//  virtual void logTransaction() const = 0;

  // won't be error, but never call the derived class function.
  virtual void logTransaction() const
  {
    std::cout << "Transaction base class virtual logTransaction" << std::endl;
  }

private:
  double price_;
};

class BuyTransaction : public Transaction
{
public:
  BuyTransaction(double price)
    : Transaction(price)
  { }

  virtual void logTransaction() const
  {
    std::cout << "BuyTransaction logTransaction" << std::endl;
  }
};

class SellTranaction : public Transaction
{
public:
  SellTranaction(double price)
    : Transaction(price)
  { }

  virtual void logTransaction() const
  {
    std::cout << "SellTranaction logTransaction" << std::endl;
  }
};

int main(int argc, char** argv)
{
  BuyTransaction b(12.0);
  // What will happen ?

  return 0;
}
