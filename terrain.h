// this file is for getting terrain information

#include "menu.h"
#include <ncurses.h>

class terrain // base class for terrains
{
public:
  terrain();
  ~terrain();
  bool display_info(char);   // displays information of the terrain in the menu
  int get_travel_cost(char); // returns cost to travel
  int get_color(char);       // returns color of terrain
};
