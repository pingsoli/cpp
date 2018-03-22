///////////////////////////////////////////////////////////////////////////////
//
// Using std::future to get the return valud of an asynchronous work
// one-off event
//
///////////////////////////////////////////////////////////////////////////////

#include <future>
#include <iostream>

int find_the_answer_to_ltuate()
{
  return 42;
}

void do_other_stuff()
{}

int main(int argc, char** argv)
{
  std::future<int> the_answer = std::async(find_the_answer_to_ltuate);
  do_other_stuff();

  std::cout << "The answer is " << the_answer.get() << std::endl;
  return 0;
}
