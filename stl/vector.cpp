////////////////////////////////////////////////////////////////////////////////
// reference
// https://stackoverflow.com/questions/17299951/c-vector-what-happens-whenever-it-expands-reallocate-on-stack
////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <iterator>

////////////////////////////////////////////////////////////////////////////////
// old C legacy APIs
void print(int *begin, std::size_t num) {
  for (int i = 0; i < num; ++i)
    printf("%d ", *(begin + i));
  putchar('\n');
}

void doSomething(char *ptr, std::size_t num) {
  for (int i = 0; i < num; ++i)
    putchar(*(ptr + i));
}
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  // {
  //   // the size of vector itself is constant.
  //   std::vector<int> vi;
  //
  //   std::cout << "vi size: " << sizeof(vi) << '\n';
  //   vi.push_back(1); // push some data to vector
  //   std::cout << "vi size after pushing data: " << sizeof(vi) << '\n';
  //
  //   // as we can see, the vector's size is constant.
  //   // The storage of the vector is handled automatically, and the elements on
  //   // vector is stored contiguously.
  //   //
  //   // use reserve() function to eliminate reallocations if the number of elements
  //   // is known beforehand.
  // }
  //
  // {
  //   // make std::vector compatible with legacy C APIs
  //   std::vector<int> arr{1, 2, 3, 4, 5, 6};
  //   // std::vector<int> arr;
  //   // std::cout << arr[0] << '\n'; // not safe
  //   print(&arr[0], arr.size());
  //
  //   // the better one implementation.
  //   if (!arr.empty())
  //     print(&arr[0], arr.size());
  //
  //   // vector<char> to replace string
  //   std::vector<char> str{'h', 'e', 'l', 'l', 'o'};
  //   if (!str.empty())
  //     doSomething(&str[0], str.size());
  //
  //   // convert std::vector<char> to string.
  //   std::string s(str.begin(), str.end());
  //   std::cout << '\n' << s << '\n';
  //
  //   if (!s.empty())
  //     doSomething(&s[0], s.size());
  // }
  //
  // {
  //   // the cost of reallocation when inserting big data.
  //   std::vector<int> vi;
  //   const int size = 100000;
  //
  //   std::cout << std::endl;
  //   auto t1 = std::chrono::high_resolution_clock::now();
  //   for (int i = 0; i < size; ++i)
  //     vi.push_back(i);
  //   auto t2 = std::chrono::high_resolution_clock::now();
  //   std::chrono::duration<double, std::milli> d = t2 - t1;
  //   std::cout << "no reserve cost " << d.count() << '\n';
  //
  //   vi.resize(0);
  //   vi.reserve(size);
  //   auto t3 = std::chrono::high_resolution_clock::now();
  //   for (int i = 0; i < size; ++i)
  //     vi.push_back(i);
  //   auto t4 = std::chrono::high_resolution_clock::now();
  //   std::chrono::duration<double, std::milli> d1 = t4 - t3;
  //   std::cout << "reserve cost " << d1.count() << '\n';
  // }
  //
  // {
  //   // downsize vector to fit size.
  //   // trick 1: use swap, needs a temp variable
  //   // trick 2: use shrick_to_fit function (since c++11)
  //   std::vector<int> vi;
  //   const int space_size = 10000;
  //   vi.reserve(space_size);
  //   vi.push_back(1);
  //   vi.push_back(3);
  //   vi.push_back(5);
  //
  //   std::cout << vi.size() << ' ' << vi.capacity() << '\n';
  //   // needs a temporary variable, copy the data from origin place, and spend
  //   // too much time on exchange data if has many data.
  //   std::vector<int>(vi).swap(vi);
  //   std::cout << vi.size() << ' ' << vi.capacity() << '\n';
  //
  //   // recover the vector capacity
  //   vi.reserve(space_size);
  //   std::cout << vi.size() << ' ' << vi.capacity() << '\n';
  //   vi.shrink_to_fit();
  //   std::cout << vi.size() << ' ' << vi.capacity() << '\n';
  // }
  //
  // {
  //   // erase-remove idiom, remove same elements from vector, string, deque.
  //   // use list::remove for std::list.
  //   // use the xxx.erase() for associated container.
  //   std::vector<int> vi;
  //
  //   vi.push_back(1);
  //   vi.push_back(2);
  //   vi.push_back(2);
  //   vi.push_back(2);
  //   vi.push_back(10);
  //   vi.push_back(2);
  //   vi.push_back(3);
  //
  //   for (auto it = vi.begin(); it != vi.end(); ++it)
  //     std::cout << &(*it) << ' ';
  //   std::cout << '\n';
  //
  //   // vi.erase(vi.end() - 1, vi.end());
  //   auto iter = std::remove(vi.begin(), vi.end(), 2);
  //   std::cout << &(*iter) << '\n';
  //   vi.erase(iter, vi.end());
  //
  //   // vi.erase(std::remove(vi.begin(), vi.end(), 2), vi.end());
  //
  //   for (auto it = vi.begin(); it != vi.end(); ++it)
  //     std::cout << &(*it) << ' ';
  //   std::cout << '\n';
  // }

  {
    // // insert a list at the end of vector
    // std::vector<int> v1{1, 2, 3, 4, 5, 6, 7};
    // std::vector<int> v2{0, 0};

    // // the following code cann't perform properly.
    // // std::transform(v1.begin(), v1.end(), v2.end(),
    // //     [](const int a) { return a + 1; });

    // // use back_inserter() instead.
    // std::transform(v1.begin(), v1.end(), std::back_inserter(v2),
        // [](const int a) { return a + 1; });

    // std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));
  }

  {
    // // insert to a empty vector
    // std::vector<int> vi;
    // vi.reserve(10);

    // vi.insert(vi.begin(), 5);
    // vi.insert(vi.begin(), 6);
    // vi.insert(vi.begin(), 7);

    // std::copy(vi.begin(), vi.end(), std::ostream_iterator<int>(std::cout, " "));
  }

  {
    // copy int array to a vector
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    std::size_t size = sizeof(arr) / sizeof(int);
    std::vector<int> vi;

    std::cout << size << '\n';
    // the following call is equivalent, but back_inserter call the push_back,
    // but inserter will call the insert() method of vector.
    // std::copy(arr, arr+size, std::back_inserter(vi));
    std::copy(arr, arr+size, std::inserter(vi, vi.begin()));

    std::copy(vi.begin(), vi.end(), std::ostream_iterator<int>(std::cout, " "));
  }

  return 0;
}
