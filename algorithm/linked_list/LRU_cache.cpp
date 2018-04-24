////////////////////////////////////////////////////////////////////////////////
//
// LRU cache
// from https://leetcode.com/problems/lru-cache/description/
//
// Difficulty: hard
//
// Design and implement a data structure for Least Recently Used(LRU) cache.
// It should support the following operations: get and put.
//
// get(key) - Get the value (will be always be postive) of the key if the key
// exists in the cache. otherwise return -1.
//
// put(key, value) - Set or insert the value if key is not already present. When
// the cache reached its capacity, it should invalidate the least recently used
// item before inserting a new item.
//
// Follow up
// Could you do both operations in O(1) time complexity ?
//
// Example
// LRUCache cache = new LRUCache(2 /* capacity */);
//
// cache.put(1, 1);
// cache.put(2, 2)
// cache.get(1);
// cache.put(3, 3); // evicts key 2
// cache.get(2);    // return -1 (not found)
// cache.put(4, 4); // evicts key 1
// cache.get(1);    // return -1 (not found)
// cache.get(3);    // return 3
// cache.get(4);    // return 4
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iterator>
#include <list>
#include <unordered_map>

class LRUCache {
public:
  LRUCache(int capacity) : capacity_(capacity) {}

  int get(int key) {
    auto it = cache.find(key);
    if (it == cache.end()) return -1;
    touch(it);
    return it->second.first;
  }

  void set(int key, int value) {
    auto it = cache.find(key);
    if (it != cache.end()) touch(it);
    else {
      if (cache.size() == capacity_) {
        cache.erase(used.back());
        used.pop_back();
      }
      used.push_front(key);
    }
    cache[key] = { value, used.begin() };
  }

private:
  typedef std::list<int> LI;
  typedef std::pair<int, LI::iterator> PII;
  typedef std::unordered_map<int, PII> HIPII;

  void touch(HIPII::iterator it) {
    int key = it->first;
    used.erase(it->second.second);
    used.push_front(key);
    it->second.second = used.begin();
  }

  HIPII cache;
  LI    used;
  int   capacity_;
};

int main(int argc, char** argv)
{
  LRUCache cache(2);

  cache.set(1, 1);
  cache.set(2, 2);
  std::cout << cache.get(1) << std::endl;
  cache.set(3, 3);
  std::cout << cache.get(2) << std::endl;
  cache.set(4, 4);
  std::cout << cache.get(1) << std::endl;
  std::cout << cache.get(3) << std::endl;
  std::cout << cache.get(4) << std::endl;

  return 0;
}
