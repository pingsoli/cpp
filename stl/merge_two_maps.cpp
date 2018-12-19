#include <map>
#include <iostream>

double mergePredicate(double lhs, double rhs) {
  return lhs + rhs;
}

// linear complexity.
template <class Map, class Merger>
void merge(Map& dst, Map& src, Merger merger) {
  auto it1 = dst.begin();
  auto it2 = src.begin();
  auto&& comp = dst.value_comp();

  for (; it1 != dst.end() && it2 != src.end();) {
    if (comp(*it1, *it2)) { // it1 '<' it2
      ++it1;
    } else if (comp(*it2, *it1)) { // it1 '>' it2
      dst.insert(it1, *it2); // with hint to have correct complexity.
      ++it2;
    } else { // equivalent
      it1->second = merger(it1->second, it2->second);
      ++it1;
      ++it2;
    }
  }
  dst.insert(it2, src.end());
}

int main(int argc, char *argv[])
{
  // std::map<int, double> mapA = { {0, 1.0}, {2, 2.0}, {4, 4.0} };
  // std::map<int, double> mapB = { {1, 1.0}, {2, 1.5}, {3, 2.5} };

  std::map<int, double> mapA = { {2, 2.0}, {4, 4.0}, {0, 1.0} };
  std::map<int, double> mapB = { {1, 1.0}, {2, 1.5}, {3, 2.5} };

  merge(mapA, mapB, mergePredicate);

  for (const auto& pair : mapA) {
    std::cout << "key: " << pair.first << ", value: " << pair.second << '\n';
  }

  return 0;
}
