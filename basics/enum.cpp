// unscoped enums and scoped enums

// C++98-style enums
// enum Color { black, white, red };
// auto black = false; // error! black already declared in this scope.

// c++11 enum class.
enum class Color { black, white, red };
auto white = false; // it's fine.

int main(int argc, char *argv[])
{
  Color w = Color::white;
  auto b = Color::black;

  return 0;
}
