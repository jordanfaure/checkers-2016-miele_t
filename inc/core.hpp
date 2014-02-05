
#ifndef __CORE_H__
# define __CORE_H__

# include "checkers.hpp"
# include "gui.hpp"
# include "referee.hpp"
# include "player.hpp"

class Core
{
public:
  Core();

  void exec();
private:
  Gui _gui;
  Referee _referee;
  Player _white;
  Player _black;
};

#endif // !__CORE_H__
