#include "frupal.h"

int main(int argc, char ** argv)
{
  initscr(); //Inits screen / sets up ncurses
  noecho();
  cbreak();

  int y,x; //height + width are the size of the ncurses window we want. y + x are the size of the entire terminal
  getmaxyx(stdscr, y, x); //Initialize y + x with the appropriate values for the screen / terminal's current size
  
  
  WINDOW * mapwin = newwin(y, x*0.75, 0, 0); //Create a new window y lines high, and 75% of x value as described by the standard screen (terminal window size)

	//vertical line seperating menu and map
	move(0, x*.75);
	vline('#', y);

	mvwprintw(stdscr, 0, x*0.75+13, "Arrow Keys to Move Cursor"); //Print out instructions to the menu
  mvwprintw(stdscr, 1, x*0.75+13, "WASD Keys to Move Cursor"); //Print out instructions to the menu
  refresh();
	/*		
  	Hero temp;
  	char tem[] = "Dynamite";
  	char des[] = "Destroys everything";
  	tool tempo(tem, des,300,10);
  	temp.addTool(&tempo);		how to call addTool function for Hero

	char var[] = "Hammer";	
	char desc[] = "weak";
	tool temporary(var,desc,15,2);
	temp.addTool(&temporary);
	
	tool * copy;
	copy = NULL;
  	if(temp.selectTool(copy) == false){}	how to call selectTool function for hero, copy becomes what was selected
						this allows for things like heroOBJ->modEner(-((obstacleOBJ.get_b_energy)/selectedTool.getDivisor))
						when breaking obstacles
	*/

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
    g = new Frupal(mapwin,5,5);
  }
  start_color();//star ncurses color

  //series of inits initializes our color pairs for drawing the map
  init_pair(1,COLOR_YELLOW, COLOR_RED);
  init_pair(2,COLOR_BLACK, COLOR_BLUE);
  init_pair(3,COLOR_BLACK, COLOR_WHITE);
  init_pair(4,COLOR_BLACK, COLOR_GREEN);
  init_pair(5,COLOR_BLACK, COLOR_MAGENTA);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_CYAN);

	bkgd(COLOR_PAIR(6));
	refresh();
  g->showMap();
  wrefresh(mapwin);
  while(g->getmv()!='q')
  {
    //Handle the Menu In Here Probably
  }

  endwin(); //Ends ncurses / deallocates memory

  delete g;

  return 0;
}
