
# include "../inc/core.hpp"

Core::Core()
{
  _white.setType(HUMAN);
  _black.setType(AI_PLAYER);
  _white.setColor(WHITE);
  _black.setColor(BLACK);
}

void Core::exec()
{
  Hit hit;
  Player *player(&_white);

  while (!_referee.isEnd())
    {
      _gui.clear();
      _gui.show();
      
      do
	{
	  if (player.getType() == HUMAN)
	    _gui.play(player.getColor(), hit);
	  else
	    player.play(hit);
      	}
      while (_referee.checkHit(hit) == false);

      
    }
}
