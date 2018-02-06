/*
 * PERFORMANCE
 * unordered_map Vs. map (ordered)
 * +----------------+---------------------+--------------------+
 * | Ordering       | Increasing order    | no ordering        |
 * |                | (by deafult)        |                    |
 * +----------------+---------------------+--------------------+
 * | Implementation | Self balancing BST  | Hash Table         |
 * +----------------+---------------------+--------------------+
 * |                | like Red-Black Tree |                    |
 * +----------------+---------------------+--------------------+
 * | Search time    | log(n)              | O(1) -> Average    |
 * |                |                     | O(1) -> Worst case |
 * +----------------+---------------------+--------------------+
 * | Insertion time | log(n) + Rebalance  | same as search     |
 * +----------------+---------------------+--------------------+
 * | Deletion time  | log(n) + Rebalance  | same as search     |
 * +----------------+---------------------+--------------------+
 *
 * reference from: https://www.geeksforgeeks.org/map-vs-unordered_map-c/
 * https://github.com/greg7mdp/sparsepp
 *
 * SUMMARY:
 * so, if we don't care about the key order, we can use unordered map.
 * In common case, we recommand unordered_map.
 */
#include <map>
#include <unordered_map>
#include <iostream>

int main(int argc, char** argv)
{
  std::map<int, int> om = {
    {1, 2}, {2, 3}, {4, 5},  {5, 6},
    {7, 8}, {9, 0}, {10, 1}, {11, 0}
  };

  std::cout << "ordered map\n";
  for (const auto& n : om)
    std::cout << "Key: [" << n.first << "] value: " << n.second << '\n';

  std::unordered_map<int, int> um = {
    {1, 2}, {2, 3}, {4, 5},  {5, 6},
    {7, 8}, {9, 0}, {10, 1}, {11, 0}
  };

  std::cout << "unordered map\n";
  for (const auto& n: um)
    std::cout << "Key: [" << n.first << "] value: " << n.second << '\n';

  return 0;
}
