#include <string>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>

uint32_t rotl(uint32_t value, unsigned int count) {
  const uint32_t mask =
    (__CHAR_BIT__ * sizeof(value) - 1);
  count &= mask;
  return (value << count) |
         (value >> ((-count)&mask));
}

uint32_t hash_char(uint32_t hash, char c)
{
  hash = rotl(hash, c); // circular rotate left
  hash ^= c;
  return hash;
}

struct HashString {
  void operator() (const std::string& s) {
    hash = std::accumulate(s.begin(), s.end(), hash, hash_char);
  }
  uint32_t hash = 0;
};

template <typename C>
uint32_t hash_all_strings(const C& v) {
  const auto hasher = for_each(v.begin(), v.end(), HashString());
  return hasher.hash;
}

void test_for_each_hash() {
  std::vector<std::string> v{"one", "two", "three", "four"};
  uint32_t hash = hash_all_strings(v);
  std::cout << "Hash: " << hash << '\n';
}

uint32_t hash_string(const std::string& s) {
  return std::accumulate(s.begin(), s.end(), 0, hash_char);
}

template <typename C>
std::vector<uint32_t> hash_each_string(const C& v) {
  std::vector<uint32_t> res;
  std::transform(v.begin(), v.end(), std::back_inserter(res), hash_string);
  return res;
}

void test_transform_hash() {
  std::vector<std::string> v{"one", "two", "Three", "four", "five"};
  auto res = hash_each_string(v);
  std::cout << "Hash: ";
  for_each(res.begin(), res.end(), [](uint32_t rh) { std::cout << rh << ' '; });
  std::cout << '\n';
}

int main(int argc, char *argv[])
{
  test_for_each_hash();
  test_transform_hash();
  return 0;
}
