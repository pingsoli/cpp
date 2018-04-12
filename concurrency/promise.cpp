///////////////////////////////////////////////////////////////////////////////
//
// std::promise and std::future
//
// References
// [1] https://stackoverflow.com/questions/11004273/what-is-stdpromise
//
///////////////////////////////////////////////////////////////////////////////

#include <exception>
#include <future>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
//
// Inactive promise
int test1()
{
  std::promise<int> pr;
  return 0;
}
// fine, no problems

///////////////////////////////////////////////////////////////////////////////
//
// Active promise, unused
int test2()
{
  std::promise<int> pr;
  auto fut = pr.get_future();
  return 0;
}
// fine, no problems, fut.get() would block indefinitely

///////////////////////////////////////////////////////////////////////////////
//
// Too many futures
int test3()
{
  std::promise<int> pr;
  auto fut1 = pr.get_future();
  auto fut2 = pr.get_future(); // Error: "Future already retrieved"
  return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// Satisfied promise
int test4()
{
  std::promise<int> pr;
  auto fut = pr.get_future();

  {
    std::promise<int> pr2(std::move(pr));
    pr2.set_value(10);
  }

  return fut.get();
}

///////////////////////////////////////////////////////////////////////////////
//
// Too much satisfaction
int test5()
{
  std::promise<int> pr;
  auto fut = pr.get_future();

  {
    std::promise<int> pr2(std::move(pr));
    pr2.set_value(10);
    pr2.set_value(10); // Error: "Promise already satisfied"
  }

  return fut.get();
}

///////////////////////////////////////////////////////////////////////////////
//
// Exception
int test6()
{
  std::promise<int> pr;
  auto fut = pr.get_future();

  {
    std::promise<int> pr2(std::move(pr));
    pr2.set_exception(std::make_exception_ptr(std::runtime_error("Booboo")));
  }

  return fut.get();
}
// throws the runtime_error exception

///////////////////////////////////////////////////////////////////////////////
//
// Broken promise
int test7()
{
  std::promise<int> pr;
  auto fut = pr.get_future();

  {
    std::promise<int> pr2(std::move(pr));
  }
  // Error: "Broken promise"

  return fut.get();
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  try
  {
//    test1();
//    test2();
//    test3();
    test4();
//    test5();
//    test6();
//    test7();
  }
  catch (std::future_error const & e)
  {
    std::cout << "Future error: " << e.what() << " / " << e.code() << std::endl;
  }
  catch (std::exception const & e)
  {
    std::cout << "Standard exception: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exception." << std::endl;
  }

  return 0;
}
