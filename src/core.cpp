
# include "../inc/core.hpp"

Core::Core()
{
}

void Core::exec()
{
  bool loop(true);

  while (loop)
    {
      this->clear();
      this->show();
    }
}


void Core::clear()
{
  system("clear");
}

void Core::show()
{
}
