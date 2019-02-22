#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char *argv[])
{
  auto displayAllElements = [] (const int& v) { std::cout << v << '\n'; };

  {
    // // Call operator= on each element
    // std::vector<int> v = {1, 2, 3, 4, 5};
    // std::fill(v.begin(), v.end(), 3);
    // std::for_each(v.begin(), v.end(), displayAllElements);
    // return 0;
  }

  {
    class MyClass
    {
    public:
      explicit MyClass(int i) : i_(i) {}
      int getValue() const { return i_; }
    private:
      int i_;
    };

    MyClass* myObjects = static_cast<MyClass*>(malloc(5 * sizeof(MyClass)));

    // Call constructor on each object, with value 3
    std::uninitialized_fill(myObjects, myObjects + 5, 3);

    for (int i = 0; i < 5; ++i)
    {
      std::cout << myObjects[i].getValue() << '\n';
    }

    free(myObjects);
    myObjects = nullptr;

    return 0;
  }

  {
    // Insert some values at the tail of the container
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::fill_n(std::back_inserter(v), 3, -1);
    std::for_each(v.begin(), v.end(), displayAllElements);
    return 0;
  }

  return 0;
}
