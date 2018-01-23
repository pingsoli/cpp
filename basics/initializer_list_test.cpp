#include "initializer_list_test.h"

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

void initializer_list_test()
{
  values({1, 2, 3, 4, 5, 6});
}
