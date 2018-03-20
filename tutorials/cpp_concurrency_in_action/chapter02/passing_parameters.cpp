///////////////////////////////////////////////////////////////////////////////
//
// Passing parameter to std::thread
// 1) passing parameters to std::thread default constructor
// 2) passing parameters to std::thread by reference
// 3) passing member function and parameter to std::thread
// 4) passing parameters to std::thread by changing the ownership
//
// NOTE:
// Don't forget t.join() or t.detach().
// If you forget, the default is t.detach().
//
///////////////////////////////////////////////////////////////////////////////

#include <thread>
#include <string>
#include <iostream>

void f(int i, const std::string& s)
{
  std::cout << "the address of the string: " << &s << std::endl;
}

///////////////////////////////////////////////////////////////////////////////

void use_thread_default_constructor()
{
  std::thread t(f, 2, "hello world");

  t.join();
}

///////////////////////////////////////////////////////////////////////////////
//
// what happens in this situation ?
// oops exits before const char* converting to std::string, that causes
// undefined behavior.
//
void oops(int some_param)
{
  char buffer[1024];
  sprintf(buffer, "%i", some_param);
  std::thread t(f, 3, buffer);

  t.detach();
}

void not_oops(int some_param)
{
  char buffer[1024];
  sprintf(buffer, "%i", some_param);
  std::thread t(f, 3, std::string(buffer));

  t.detach();
}

///////////////////////////////////////////////////////////////////////////////
//
// std::ref used to pass reference to std::thread

typedef unsigned widget_id;

struct widget_data
{
  unsigned    id;
  std::string name;

  widget_data(unsigned id_ = 0, const std::string& name_ = "hello")
    : id{id_}, name{name_}
  {}
};

void update_data_for_widget(widget_id w, widget_data& data)
{
  data.id = 100;
  std::cout << "Change id to: "<< data.id << std::endl;
}

void process_widget_data(const widget_data& data)
{
  std::cout << "Changed id: " << data.id << std::endl;
}

void oops_again(widget_id w)
{
  widget_data data;
  std::thread t(update_data_for_widget, w, std::ref(data));
//  std::thread t(update_data_for_widget, w, data); // error
  t.join();
  process_widget_data(data);
}

///////////////////////////////////////////////////////////////////////////////
//
// call member function of class and pass parameter to it

class X
{
public:
  void do_lengthy_work(int num)
  {
    std::cout << "do_lengthy_work: " << num << std::endl;
  }
};

void pass_param_to_member_func()
{
  X my_x;
  int num = 3;
  std::thread t(&X::do_lengthy_work, &my_x, 3);
  t.join();
}

///////////////////////////////////////////////////////////////////////////////
//
// std::unique_ptr only has one copy, std::move changes the ownership of
// std::unique_ptr to std::thread

struct big_object
{
  int data;
  void prepare_data(int data_)
  {
    data = data_;
  }
};

void process_big_object(std::unique_ptr<big_object> bop)
{}

void move_to_thread()
{
  std::unique_ptr<big_object> p(new big_object);
  p->prepare_data(42);
  std::thread t(process_big_object, std::move(p));
  t.join();
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
//  use_thread_default_constructor();

//  oops(3);
//  not_oops(3);
//  oops_again(0);

//  pass_param_to_member_func();

  move_to_thread();

  return 0;
}
