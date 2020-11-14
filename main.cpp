#include "grovnik.h"

int main()
{
  initscr(); //Inits screen / sets up ncurses
  noecho();
  cbreak();

  int y,x; //height + width are the size of the ncurses window we want. y + x are the size of the entire terminal
  getmaxyx(stdscr, y, x); //Initialize y + x with the appropriate values for the screen / terminal's current size
  
  
  WINDOW * mapwin = newwin(y, x*0.75, 0, 0); //Create a new window y lines high, and 75% of x value as described by the standard screen (terminal window size)
  wborder(mapwin, 32,35,32,32,32,35,32,35); //create border using # character (integer representation = 35) along the right edge of the map window


  mvwprintw(stdscr, 0, x*0.75+13, "Arrow Keys to Move Cursor"); //Print out instructions to the menu
  refresh();

  Frupal * g = new Frupal(mapwin,1,1);
  while(g->getmv()!='q')
  {
    //menuref(stdscr...
    //refresh();
    g -> disp();
    wrefresh(mapwin);
  }

  endwin(); //Ends ncurses / deallocates memory

  return 0;
}