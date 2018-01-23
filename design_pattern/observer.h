#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Book;
class Pen;
class Computer;

class ICartVisitor
{
public:
  virtual int Visit(Book &) = 0;
  virtual int Visit(Pen &) = 0;
  virtual int Visit(Computer &) = 0;
};

class IElement
{
public:
  virtual int accept(ICartVisitor& cartVisitor) = 0;
  virtual int getPrice() = 0;
};

class Book : public IElement
{
public:
  int accept(ICartVisitor& cartVisitor)
  {
    return cartVisitor.Visit(*this);
  }
  int getPrice()
  {
    return 100;
  }
};

class Pen : public IElement
{
public:
  int accept(ICartVisitor& cartVisitor)
  {
    return cartVisitor.Visit(*this);
  }

  int getPrice()
  {
    return 10;
  }
};

class Computer : public IElement
{
public:
  int accept(ICartVisitor& cartVisitor)
  {
    return cartVisitor.Visit(*this);
  }

  int getPrice()
  {
    return 5000;
  }
};

class CartVisitor : public ICartVisitor
{
public:
  int Visit(Book& book)
  {
    return book.getPrice();
  }

  int Visit(Pen& pen)
  {
    return pen.getPrice();
  }

  int Visit(Computer& computer)
  {
    return computer.getPrice();
  }
};

#endif 
