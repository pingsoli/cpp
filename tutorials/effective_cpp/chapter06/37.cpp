///////////////////////////////////////////////////////////////////////////////
//
// Item 37: Never redefine a function's inherited default parameter value.
//
///////////////////////////////////////////////////////////////////////////////
//
// Static type and dynamic type ?
//
// static binding is early bounding, and dynamic binding is known as late
// binding.
//
///////////////////////////////////////////////////////////////////////////////
//
// Things to remember
//
// Never redefine an inherited default parameter value, because default
// parameter values are statically bound, while virtual functions - the only
// functions you should be redefining - are dynamically bound.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

///////////////////////////////////////////////////////////////////////////////
//
// class Shape
// {
// public:
//   enum ShapeColor { Red, Green, Blue };
//   virtual void draw(ShapeColor color = Red) const = 0;
// };
//
// class Rectangle : public Shape
// {
// public:
//   // Notice the different parameter vlaue - bad!
//   void draw(ShapeColor color = Green) const
//   {
//     std::cout << "Rectangle draw " << color << std::endl;
//   }
// };
//
// class Circle : public Shape
// {
// public:
//   void draw(ShapeColor color) const
//   {
//     std::cout << "Circle draw " << color << std::endl;
//   }
// };
//
///////////////////////////////////////////////////////////////////////////////

class Shape
{
public:
  enum ShapeColor { Red, Green, Blue };
  virtual void draw(ShapeColor color = Red) const = 0;
};

class Rectangle : public Shape
{
public:
  virtual void draw(ShapeColor color) const
  {
    std::cout << "Rectangle draw(ShapeColor) " << color << std::endl;
  }
};

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////

//  Shape* ps;                  // static type == Shape*
//  Shape* pr = new Rectangle;  // static type == Shape*
//  Shape* pc = new Circle;     // static type == Shape*
//
//  pr->draw(Shape::Blue);
//  pc->draw(Shape::Blue);
//
//  ps = pr; // ps's dynamic type is now Circle*
//  ps = pc; // ps's dynamic type is now Rectangle*

  /////////////////////////////////////////////////////////////////////////////

  Shape* ps;
  Shape* pr = new Rectangle;

  pr->draw();

  /////////////////////////////////////////////////////////////////////////////

  return 0;
}
