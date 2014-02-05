
#ifndef __CHECKERS_H__
# define __CHECKERS_H__

# define BOARD_SIZE 10

enum PlayerType {HUMAN, AI_PLAYER};

enum PlayerColor {NO_COLOR, BLACK, WHITE};

struct Hit
{
  unsigned int line;
  unsigned int column;
  PlayerColor color;
};

#endif // !__CHECKERS_H__
