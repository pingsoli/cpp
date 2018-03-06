#include <initializer_list>
#include <iostream>

/*
 * NOTE:
 * std::initializer_list takes only one type, if you need different types,
 * you can use variadic templates.
 */

void values(std::initializer_list<int> intValues)
{
  std::cout << "Initializer list having " << intValues.size() << std::endl;

  for
  (
    std::initializer_list<int>::const_iterator begin = intValues.begin();
    begin != intValues.end();
    ++begin
  )
    std::cout << "Value: " << *begin << "\n";
}

int main(int argc, char** argv)
{
  values({1, 2, 3, 4, 5, 6});  // Ok
//  values(1, 2, 3, 4, 5, 6);  // Error

  return 0;
}
