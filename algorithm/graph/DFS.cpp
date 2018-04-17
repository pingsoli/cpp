///////////////////////////////////////////////////////////////////////////////
//
// DFS(Depth First Search) with adjacency matrix
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stack>

const unsigned int N = 5;
int visited[N] = { 0, };

int maze[N][N] = {
//  0  1  2  3  4
  { 0, 1, 1, 0, 0 }, // 0
  { 0, 0, 1, 1, 0 }, // 1
  { 0, 1, 1, 1, 0 }, // 2
  { 1, 0, 0, 0, 0 }, // 3
  { 0, 0, 1, 1, 0 }  // 4
};

void DFS(int maze[][N], int start)
{
  visited[start] = 1;
  for (unsigned i = 0; i < N; ++i)
  {
    if (!visited[i] && maze[start][i] == 1)
      DFS(maze, i);
  }

  std::cout << start << ' ';
}

void DFS_without_recursion(int maze[][N], int start)
{
  std::stack<int> stack_;
  stack_.push(start);

  visited[start] = 1;

  bool is_push = false;

  while (!stack_.empty())
  {
    is_push = false;
    int v = stack_.top();

    for (unsigned i = 0; i < N; ++i)
    {
      if (maze[v][i] == 1 && !visited[i])
      {
        visited[i] = 1;
        stack_.push(i);
        is_push = true;
        break;
      }
    }

    if (!is_push)
    {
      std::cout << v << ' ';
      stack_.pop();
    }
  }
}

int main(int argc, char** argv)
{
  for (unsigned i = 0; i < N; ++i)
  {
    if (visited[i] == 1)
      continue;

//    DFS(maze, i);
    DFS_without_recursion(maze, i);
  }
  std::cout << std::endl;

  return 0;
}
