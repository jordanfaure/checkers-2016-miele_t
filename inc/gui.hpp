
#ifndef __GUI_H__
# define __GUI_H__

# include "checkers.hpp"

class Gui
{
public:
  Gui();
  
  void clear();
  void show();
  void play(PlayerColor color, Hit &hit);
  void updateBoard(const Hit & hit);
private:
  char board[BOARD_SIZE][BOARD_SIZE];
};

#endif // !__GUI_H__
