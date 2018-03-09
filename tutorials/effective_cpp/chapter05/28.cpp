/////////////////////////////////////////////////////////////////////////////
//
// Item 28: Avoid returning "handles" to object internals.
//
// Avoid returning handles (references, pointers, or iterators) to object
// internals. Not returning handles increases encapsulation, helps const member
// functions act const, and minimizes the creation of dangling handles.
//
///////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <iostream>

class Point
{
public:
  Point(int x = 0, int y = 0)
    : x_{x}, y_{y}
  { }

  void setX(int newVal)
  {
    x_ = newVal;
  }

  void setY(int newVal)
  {
    y_ = newVal;
  }

  int getX() const
  {
    return x_;
  }

  int getY() const
  {
    return y_;
  }

private:
  int x_, y_;
};

struct RectData
{
  Point ulhc;
  Point lrhc;
};

class Rectangle
{
public:
  Rectangle(Point ulhc, Point lrhc)
    : pData{std::make_shared<RectData>()}
  {
    pData->ulhc = ulhc;
    pData->lrhc = lrhc;
  }

  /////////////////////////////////////////////////////////////////////////////
  //
  // both functions return references to private but the purpose is keeping
  // private member constant

//  Point& upperLeft() const
//  {
//    return pData->ulhc;
//  }
//
//  Point& lowerRight() const
//  {
//    return pData->lrhc;
//  }

  ////////////////////////////////////////////////////////////////////////////
  //
  // so, add the const restraint

  const Point& upperLeft() const
  {
    return pData->ulhc;
  }

  const Point& lowerRight() const
  {
    return pData->lrhc;
  }

  ////////////////////////////////////////////////////////////////////////////

private:
  std::shared_ptr<RectData> pData;
};

void print(const Rectangle& rect)
{
  std::cout
    << "[ (" << rect.upperLeft().getX() << ", "
           << rect.upperLeft().getY() << "), "

    << '(' << rect.lowerRight().getX() << ", "
           << rect.lowerRight().getY() << ") ]"

    << std::endl;
}

int main(int argc, char** argv)
{
  Point p1(1, 2);
  Point p2(2, 3);

  Rectangle rect(p1, p2);
  print(rect);

  rect.upperLeft().setX(100);
  rect.lowerRight().setY(100);

  print(rect);

  return 0;
}
