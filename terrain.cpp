//source code for terrain classes

#include <ncurses.h>
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
}
