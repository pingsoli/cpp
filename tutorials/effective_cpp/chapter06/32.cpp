///////////////////////////////////////////////////////////////////////////////
//
// Item 32: Make sure public inheritance models "is-a"
//
// Things to remember:
// Public inheritance means "is-a". Everything that applies to base classes
// must also apply to derived classes, because every derived class object is a
// base class object.
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>

class Rectangle
{
public:
  Rectangle(int width = 0, int height = 0)
    : width_{width}, height_{height}
  {}

  virtual int width() const { return width_; }
  virtual int height() const { return height_; }
  virtual void set_width(int w) { width_ = w; }
  virtual void set_height(int h) { height_ = h; }

private:
  int width_, height_;
};

class Square : public Rectangle
{
public:
  Square(int side_length)
    : Rectangle(side_length, side_length)
  {}

  void set_width(int w)
  {
    Rectangle::set_width(w);
    Rectangle::set_height(w);
  }

  void set_height(int h)
  {
    Rectangle::set_width(h);
    Rectangle::set_height(h);
  }
};

void make_bigger(Rectangle& r)
{
  int old_height = r.height();
  r.set_width(r.width() + 10);

//  assert(r.height() == old_height);
}

int main(int argc, char** argv)
{
  Square s(10);

  assert(s.width() == s.height());

  make_bigger(s);

  assert(s.width() == s.height());

  return 0;
}
