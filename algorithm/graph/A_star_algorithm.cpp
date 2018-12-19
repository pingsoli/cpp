

// path finding algorithm.

// the source code is from geeksforgeeks website.
// https://www.geeksforgeeks.org/a-search-algorithm/

#include <pair>
#include <iostream>

#define ROW 9
#define COL 10

// typedef std::pair<int, int> Pair;
// typedef std::pair<double, Pair> pPair;
using Pair  = std::pair<int, int>;
using pPair = std::pair<double, Pair>;

struct cell {
  // Row and Column index of its parent
  // Note that 0 <= i <= ROW - 1 & 0 <= j <= COL - 1
  int parent_i, parent_j;

  // f = g + h
  // g --> the movement cost to move from the starting point to a given square
  // on the grid.
  // h --> the estimated movement cost to move from that given square on the
  // grid to the final destination.
  double f, g, h;
};


// A utility function to check whether given cell is a valid cell or not.
bool isValid(int row, int col) {
  return ((row >= 0) && (row < ROW) &&
          (col >= 0) && (col < COL));
}

// A utility function to check whether the given cell is blocked or not.
bool isUnBlocked(int grid[][COL], int row, int col) {
  if (grid[row][col] == 1)
    return true;
  else
    return false;
}

// A utility function to calculate the 'h' heuristics
double calculateHValue(int row, int col, Pair dst) {
  return ((double) std::sqrt((row - dst.first) * (row - dst.first)
                           + (col - dst.second) * (col - dst.second)));
}

// A utility function to trace the path from the source to destination
void tracePath(cell cellDetails[][COL], Pair dst) {
  int row = dst.first;
  int col = dst.second;

  std::stack<Pair> Path;
  while (!cellDetails[row][col].parent_i == row
        &&cellDetails[row][col].parent_j == col)
  {
    Path.push(std::make_pair(row, col));
    int tmp_row = cellDetails[row][col].parent_i;
    int tmp_col = cellDetails[row][col].parent_j;
    row = tmp_row;
    col = tmp_col;
  }

  path.push(std:make_pair(row, col));
  while (!Path.empty()) {
    std:pair<int, int> p = Path.top();
    Path.pop();
    std::cout << "->(" << p.first << "," << p.second << ")";
  }
}

int main(int argc, char *argv[])
{
  // 1 --> The cell is not blocked
  // 0 --> The cell is blocked
  int gird[ROW][COL] =
  {
    { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
    { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
    { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
    { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
    { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
    { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
    { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
    { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
  };

  // Source is the left-most bottom-most corner
  Pair src = std::make_pair(8, 0);

  // Destination is the left-most top-most corner
  Pair dst = std::make_pair(0, 0);

  aStartSearch(grid, src, dst);

  return 0;
}
