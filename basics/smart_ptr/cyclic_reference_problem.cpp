// discuss the cyclic references in shared_ptr
// the dependency relationship is a circle, A depends on B, B depends on A.

#include <memory>
#include <string>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// cyclic references
// the following is two-dependencies depend each other. I omit the self-dependent
// relationship.
struct B;
struct A {
  ~A () { std::cout << "~A()" << '\n'; }
  std::shared_ptr<B> b;
};

struct B {
  ~B() { std::cout << "~B()" << '\n'; }
  std::shared_ptr<A> a;
};

// solve cyclic references
struct D;
struct C {
  ~C() { std::cout << "~C()" << '\n'; }
  std::weak_ptr<D> d;
};

struct D {
  ~D() { std::cout << "~D()" << '\n'; }
  std::weak_ptr<C> c;
};

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  {
    // create cyclic references
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();

    a->b = b;
    b->a = a;
    // what happened ?
    // the resource willl be not release. because the a and b has two use counts.
    // inner members a and b point to the each other.
    // In other words, A keeps B alive and B keeps A alive.
    // In the end, we can see the destructor not be called.
  }

  {
    // solve cyclic references
    auto c = std::make_shared<C>();
    auto d = std::make_shared<D>();

    c->d = d;
    d->c = c;

    if (auto p = c->d.lock()) {
      std::cout << p.use_count() << '\n'; // 2, p and c share the same place.
    }
  }

  return 0;
}
