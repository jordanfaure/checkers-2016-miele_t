
#ifndef __PLAYER_H__
# define __PLAYER_H__

# include "checkers.hpp"

class Player
{
public:
  Player();

  void setType(PlayerType type);
  void setColor(PlayerColor color);
  void type() const;
  void color() const;
  void play(hit &hit);
private:
  PlayerType _type;
  PlayerColor _color;
};

#endif // !__PLAYER_H__
