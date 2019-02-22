#include <iostream>
#include <set>
#include <iterator>
#include <cctype>    // for std::tolower
#include <algorithm> // for std::equal

int main(int argc, char *argv[])
{

  // Specify comparator(case insentive) for set
  {
    // operator== and operator< to make associative container understand
    // equality and equivalence.

    struct InsensitiveCompare {
      bool operator()(const std::string& a, const std::string& b) const {
        return !(std::equal(a.begin(), a.end(),
                          b.begin(), b.end(),
                          [] (char a, char b) {
                            return std::tolower(a) == std::tolower(b);
                          }));
      }
    };

    // the default comparison function is std::less, the possible implementation
    // is:
    // constexpr bool operator()(const T &lhs, const T &rhs) const {
    //   return lhs < rhs;
    // }
    std::set<std::string, InsensitiveCompare> str;
    // std::set<std::string> str;

    str.insert("pingsoli");
    str.insert("PingsOli"); // won't be inserted when using case insensitive comparator of std::set
    str.insert("hello");
    str.insert("world");

    for (const auto& s : str) std::cout << s << '\n';

    // if we find "PingsOli" from set
    if (std::find(str.begin(), str.end(), "PingsOli") != str.end())
      std::cout << "Found" << '\n';
    else
      std::cout << "Not Found" << '\n';

    return 0;
  }

  // std::set use operator< to do comparison
  {
    // specify operator< within class to do comparasion in std::set
    // struct Foo {
    //   int val1;
    //   int val2;
    //
    //   Foo(int v1, int v2) : val1(v1), val2(v2) {}
    //   bool operator<(const Foo& foo) const { return val2 < foo.val2; }
    // };
    //
    // std::multiset<Foo> ms;
    // ms.insert(Foo(1, 6));
    // ms.insert(Foo(2, 5));
    // ms.insert(Foo(3, 4));
    // ms.insert(Foo(1, 4));
    //
    // for (auto const &foo : ms)
    //   std::cout << foo.val1 << " " << foo.val2 << '\n';
    //
    // return 0;
  }

  {
    // // define our compare function in associative container
    // //
    // // the below try is illegal.
    // // bool stringPtrLess(const std::string* ps1, const std::string* ps2) {
    // //   return *ps1 < *ps2;
    // // }
    // struct stringPtrLess {
    //   bool operator()(const std::string* ps1, const std::string* ps2) const {
    //     return *ps1 < *ps2;
    //   }
    // };
    //
    // // make the template
    // // struct DereferenceLess {
    // //   template <typename PtrType>
    // //   bool operator() (PtrType pt1, PtrType pt2) const {
    // //     return *pt1 < *pt2;
    // //   }
    // // };
    //
    // // std::set<std::string*, DereferenceLess> ssp;
    // std::set<std::string*, stringPtrLess> ssp;
    // ssp.insert(new std::string("hello"));
    // ssp.insert(new std::string("world"));
    // ssp.insert(new std::string("pingsoli"));
    // ssp.insert(new std::string("test"));
    //
    // for (auto it = ssp.cbegin(); it != ssp.cend(); ++it)
    //   std::cout << **it << '\n';
  }

  {
    // std::set<int, std::greater<int>> s;
    //
    // s.insert(40);
    // s.insert(30);
    // s.insert(60);
    // s.insert(20);
    // s.insert(50);
    // s.insert(50); // only one 50 will be added to the set
    // s.insert(10);
    //
    // std::set<int, std::greater<int>>::iterator itr;
    // std::cout << "\nThe set s is: " << '\n';
    // for (itr = s.begin(); itr != s.end(); ++itr)
    //   std::cout << '\t' << *itr;
    // std::cout << '\n';
    //
    // // assigning the elements from s to s1
    // std::set<int> s1(s.begin(), s.end());
    // std::cout << "\nThe set s1 after assign from s is: " << '\n';
    // for (itr = s1.begin(); itr != s1.end(); ++itr)
    //   std::cout << '\t' << *itr;
    // std::cout << '\n';
    //
    // // remove all elements up to 30 in s1
    // s1.erase(s1.begin(), s1.find(30));
    // for (itr = s1.begin(); itr != s1.end(); ++itr)
    //   std::cout << '\t' << *itr;
    // std::cout << '\n';
    //
    // // lower-bound and upper-bound for set s
    // std::cout << *s.lower_bound(40) << '\n';
    // std::cout << *s.upper_bound(40) << '\n';
    //
    // // lower-bound and upper-bound for set s1
    // std::cout << *s1.lower_bound(40) << '\n';
    // std::cout << *s1.upper_bound(40) << '\n';
  }

  return 0;
}
