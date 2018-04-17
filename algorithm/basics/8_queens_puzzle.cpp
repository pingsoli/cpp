///////////////////////////////////////////////////////////////////////////////
//
// Eight Queens Puzzle
//
// Target
// Print all eight-queens-puzzle solutions
//
// All solutions:
//
// References
//
///////////////////////////////////////////////////////////////////////////////


#include <iostream>

const int N = 8;
int position[N];
int solutions{0};

// Recursive
bool is_safe(int queen_number, int row_position)
{
  for (int i = 0; i < queen_number; ++i)
  {
    // Get another queen's row position
    int other_row_pos = position[i];

    if (other_row_pos == row_position || // Same row
        other_row_pos == row_position - (queen_number - i) || // Same diagonal
        other_row_pos == row_position + (queen_number - i)) // Same disgonal
      return false;
  }
  return true;
}


void solve(int k)
{
  if (k == N)
  {
    std::cout << "Solution: ";
    for (int i = 0; i < N; ++i)
      std::cout << position[i] << ' ';
    std::cout << std::endl;

    ++solutions;
  }
  else
  {
    for (int i = 0; i < N; ++i)
    {
      if (is_safe(k, i))
      {
        position[k] = i;
        solve(k + 1);
      }
    }
  }
}

int main(int argc, char** argv)
{
  solve(0);

  std::cout << solutions << std::endl;
  return 0;
}
