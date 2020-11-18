#include "frupal.h"

int main(int argc, char ** argv)
{
  initscr(); //Inits screen / sets up ncurses
  noecho();
  cbreak();

  int y,x; //height + width are the size of the ncurses window we want. y + x are the size of the entire terminal
  getmaxyx(stdscr, y, x); //Initialize y + x with the appropriate values for the screen / terminal's current size
  
  
  WINDOW * mapwin = newwin(y, x*0.75, 0, 0); //Create a new window y lines high, and 75% of x value as described by the standard screen (terminal window size)

	move(0, x*.75);
	vline('#', y);
  mvwprintw(stdscr, 0, x*0.75+13, "Arrow Keys to Move Cursor"); //Print out instructions to the menu
  refresh();

  Frupal * g;
  bool goodMapFile = false;
  //Attempt to load the map from a file if one was provided as a command line argument.
  if(argc > 1)
  {
    g = new Frupal(mapwin,argv[1]);
    goodMapFile = g->mapLoaded();
    if(!goodMapFile)
      delete g;
  }
  //If we were not given a map file, or the map file wasn't correct, load the default map.
  if(!goodMapFile)
  {
    g = new Frupal(mapwin,1,1);
  }

  while(g->getmv()!='q')
  {
    //menuref(stdscr...
    //refresh();
    wrefresh(mapwin);
  }

  endwin(); //Ends ncurses / deallocates memory

  delete g;

  return 0;
}
