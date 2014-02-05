
#ifndef __REFEREE_H__
# define __REFEREE_H__

# include "checkers.hpp"

class Referee
{
public:
  Referee();
  
  bool isEnd();
  bool checkHit(const Hit & hit);
  void updateBoard(const Hit & hit);
  PlayerColor getCaseColor(unsigned int line, unsigned int column);
private:
  bool _loop;
  char _board[BOARD_SIZE][BOARD_SIZE];
};

#endif // !__REFEREE_H__
