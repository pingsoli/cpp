#ifndef __GAME_PLAYER_H__
#define __GAME_PLAYER_H__

#include <string>

class GamePlayer
{
private:
  static const int NUM_TURNS = 5;
  enum { num_turns = 5 };  // enum hack

  int score[NUM_TURNS];
  int another_score[num_turns];

  std::string name;

public:
  int getTurns();
  int getAnotherTurns();
};

#endif /* __GAME_PLAYER_H__ */
