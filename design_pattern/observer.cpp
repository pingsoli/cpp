#include <iostream>
#include "observer.h"
#include "observer_new.h"
#include <string>
#include "event_type.h"

void foo(int  i)
{
  std::cout << "foo( " << i << " )\n";
}

void bar()
{
  std::cout << "bar()\n";
}

void test_observer_1()
{
  Subject<EventType> s;

  s.registerObserver(EventType::GREEN, bar);
  s.registerObserver(EventType::ORANGE, std::bind(foo, 42));
  s.registerObserver(EventType::RED, std::bind(foo, 12345));

  s.notify(EventType::GREEN);
  s.notify(EventType::RED);
  s.notify(EventType::ORANGE);
}

void test_observer_2()
{
  Subject<std::string> s;
  s.registerObserver("GREEN", bar);
  s.registerObserver("ORANGE", std::bind(foo, 42));
  s.registerObserver("RED", std::bind(foo, 12345));

  const std::string msg("hello world");
  s.registerObserver("RED", [&msg]{std::cout << msg << std::endl;});

  s.notify("GREEN");
  s.notify("RED");
  s.notify("ORANGE");
}

int main(int argc, char **argv)
{
//  int total = 0;
//
//  ICartVisitor *cart = new CartVisitor();
//  Book book;
//  Pen pen;
//  Computer computer;
//
//  total += cart->Visit(book);
//  total += cart->Visit(pen);
//  total += cart->Visit(computer);
//    
//  std::cout << total << std::endl;
//  // 5510

  test_observer_1();
//  test_observer_2();

  return 0;
}
