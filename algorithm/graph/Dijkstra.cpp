///////////////////////////////////////////////////////////////////////////////
//
// Dijkstra algorithm
// 1) make use of priority queue
//
// the following implemenation efficiency: O(m log n)
//
///////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <iostream>
#include <set>
#include <vector>
#include <utility>

// Prerequisites
// 1) the vertices are labeled 0 through n-1
// 2) graph[x] is the list of directed edges from vertex x
// 3) the edge lengths are zero or positve, and small enough so that no
// temporary distance will overflow an int.

struct edge { int to, length; };

int dijkstra(std::vector<std::vector<edge>> &graph, int source, int target)
{
  std::vector<unsigned> min_distance(graph.size(), INT_MAX);
  min_distance[source] = 0;
  std::set<std::pair<int, int>> active_vertices;
  active_vertices.insert({0, source});

  while (!active_vertices.empty()) {
    int where = active_vertices.begin()->second;
    if (where == target) return min_distance[where];
    active_vertices.erase(active_vertices.begin());

    for (auto ed : graph[where])
      if (min_distance[ed.to] > min_distance[where] + ed.length) {
        active_vertices.erase({ min_distance[ed.to], ed.to });
        min_distance[ed.to] = min_distance[where] + ed.length;
        active_vertices.insert({ min_distance[ed.to], ed.to });
      }
  }
  return INT_MAX;
}

int main(int argc, char** argv)
{
  //         4
  //       /   \
  //     9/     \6
  //     /       \
  //    / 2    11 \
  //   5 --- 2 --- 3
  //   |   / |    /
  // 14| 9/  |10 /15
  //   | /   |  /
  //   0 --- 1
  //      7

  std::vector<std::vector<edge>> graph =
  {
    {{0,0},       {1,7},       {2,9},       {3,INT_MAX}, {4,INT_MAX}, {5,14}},
    {{0,7},       {1,0},       {2,10},      {3,15},      {4,INT_MAX}, {5,INT_MAX}},
    {{0,9},       {1,10},      {2,0},       {3,11},      {4,INT_MAX}, {5,2}},
    {{0,INT_MAX}, {1,15},      {2,11},      {3,0},       {4,6},       {5,INT_MAX}},
    {{0,INT_MAX}, {1,INT_MAX}, {2,INT_MAX}, {3,6},       {4,0},       {5,9}},
    {{0,14},      {1,INT_MAX}, {2,2},       {3,INT_MAX}, {4,9},       {5,0}}
  };

  int source{0}, target{0};
  source = 0;
  target = 4;

  int distance = dijkstra(graph, 0, 4);

  std::cout << "from " << source << " to " << target << ": " << distance
    << std::endl;

  return 0;
}
