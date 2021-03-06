#include <map>
#include <string>
#include <memory>
#include <iostream>

int main(int argc, char *argv[])
{
  {
    // // delete resource by ownself.
    // // std::string *str = new std::string("hello");
    // std::map<int, std::string*> m;
    // m[1] = str;
    //
    // //delete str; // release the memory, what happened in std::map ? dangerous.
    // for (auto it = m.begin(); it != m.end(); ++it)
    //   std::cout << it->first << ", " << *it->second << '\n';
    //
    // // the better way, we don't need to delete the resource by ownself.
    // // shared_ptr
    // std::shared_ptr<std::string> ss = std::make_shared<std::string>("hello");;
  }

  {
    // remove/erase the contents(may duplicate) from map
    std::map<int, char> mi = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}};
    auto it = mi.begin();
    int matched_value = 2;

    // value_type<const K, V>, it's more effective than complex object.
    mi.insert(std::map<int, char>::value_type(5, 'e'));

    // compare the following with the below, which is better ?
    // the former is absolutely better in complex object.
    mi[6] = 'f';

    while (it != mi.end()) {
      if (it->first == matched_value)
        mi.erase(it);
      ++it;
    }

    for (auto it = mi.begin(); it != mi.end(); ++it)
      std::cout << it->first << ' ' << it->second << '\n';
  }

  {
    // build one-to-one, one-to-many relationship
    //
    // multimap<x, y> and map<x, vector<y>> which is better ?
    // multimap's iterator remains valid until erased from map.
    // map<x, vector<y>> may have empty value set with existing key.
    // prefer multimap than map of vectors.
  }

  {
    // emplace data(implicity constructor), and clear the map, check out the data.
    std::map<int, std::string> mymap;

    mymap.emplace(1, "hello");
    mymap.emplace(2, "world");
    mymap.emplace(3, "test");

    // traverse the map
    for (auto it = mymap.begin(); it != mymap.end(); ++it)
      std::cout << it->first << " : " << it->second.data() << '\n';

    mymap.clear();

    std::cout << "after clearing the map ..." << '\n';
    for (auto it = mymap.begin(); it != mymap.end(); ++it)
      std::cout << it->first << " : " << it->second.data() << '\n';
  }

  return 0;
}
