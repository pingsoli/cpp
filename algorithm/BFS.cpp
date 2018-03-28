///////////////////////////////////////////////////////////////////////////////
//
// BFS (Breadth First Search)
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <queue>

const unsigned int N = 5;

int visited[N + 1] = { 0, };

int maze[N][N] = {
  {0, 1, 1, 0, 0},
  {0, 0, 1, 1, 0},
  {0, 1, 1, 1, 0},
  {1, 0, 0, 0, 0},
  {0, 0, 1, 1, 0}
};

void BFS(int maze[][N], int start)
{
  std::queue<int> queue_;
  queue_.push(start);

  visited[start] = 1;

  while (!queue_.empty())
  {
    int front = queue_.front();
    std::cout << front << ' ';
    queue_.pop();

    for (int i = 1; i < N + 1; ++i)
    {
      if (!visited[i] && maze[front - 1][i - 1] == 1)
      {
        visited[i] = 1;
        queue_.push(i);
      }
    }
  }
}

int main(int argc, char** argv)
{
  for (int i = 1; i < N + 1; ++i)
  {
    if (visited[i] == 1)
      continue;
    BFS(maze, i);
  }
  std::cout << std::endl;

  return 0;
}
