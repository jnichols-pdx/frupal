//source code for terrain classes

#include "terrain.h"

terrain::terrain(): travel_cost(0), color(0){}

terrain::~terrain(){}

int terrain::get_color(){
	return color;
}
 
int terrain::get_travel_cost(){
	return travel_cost;
}

//----------------------------------------------------------------------------

meadow::meadow()
{
	color = COLOR_GREEN;
	travel_cost = 1;
}    

meadow::~meadow(){}

void meadow::display_info()
{
	int y = 9;   	//change this variable to move the position of the text up or down
	int x = 3;      //change this to move it right or left
	mvwprintw(stdscr, y, COLS*0.75+x, "Meadow");
	mvwprintw(stdscr, y+1, COLS*0.75+x, "Cost to move through is 1 energy");
	mvwprintw(stdscr, y+2, COLS*0.75+x, "                                          ");
}

//----------------------------------------------------------------------------

swamp::swamp()
{
	color = COLOR_MAGENTA;
	travel_cost = 2;
}

swamp::~swamp(){}

void swamp::display_info()
{
	int y = 9;   	//change this variable to move the position of the text up or down
	int x = 3;      //change this to move it right or left
	mvwprintw(stdscr, y, COLS*0.75+x, "Swamp   ");
	mvwprintw(stdscr, y+1, COLS*0.75+x, "Cost to move through is 2 energy");
	mvwprintw(stdscr, y+2, COLS*0.75+x, "                                         ");
}

//----------------------------------------------------------------------------

water::water()
{
	color = COLOR_BLUE;
	travel_cost = 0;
}

water::~water(){}


void water::display_info()
{
	int y = 9;   	//change this variable to move the position of the text up or down
	int x = 3;      //change this to move it right or left
	mvwprintw(stdscr, y, COLS*0.75+x, "Water    ");
	mvwprintw(stdscr, y+1, COLS*0.75+x, "Cost to move through is 0 energy");
	mvwprintw(stdscr, y+2, COLS*0.75+x, "A Boat is required to move through      ");
}

//----------------------------------------------------------------------------

wall::wall()
{
	color = COLOR_WHITE;
	travel_cost = 1;
}

wall::~wall(){}

void wall::display_info()
{
	int y = 9;   	//change this variable to move the position of the text up or down
	int x = 3;      //change this to move it right or left
	mvwprintw(stdscr, y, COLS*0.75+x, "Wall         ");
	mvwprintw(stdscr, y+1, COLS*0.75+x, "You can't pass through                ");
	mvwprintw(stdscr, y+2, COLS*0.75+x, "An attempt to do so will cost 1 energy");
}
