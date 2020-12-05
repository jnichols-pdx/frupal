//source code for terrain classes

#include "terrain.h"

terrain::terrain(){}

terrain::~terrain(){}

using namespace::menu;

//returns ncurses color constant for terrain type
//terrain type passed in as character representation 
int terrain::get_color(char terType){
	int color = COLOR_PAIR(0);

	switch(terType){
		case '~': //water
			color = COLOR_PAIR(2);
			break;
		case '=': //wall
			color = COLOR_PAIR(3);
			break;
		case '.': //meadow
			color = COLOR_PAIR(4);
			break;
		case '"': //swamp
			color = COLOR_PAIR(5);
			break;
		default:	
			break;
	}
	return color;
}

//returns travel cost of certain terrain type passed in as char
int terrain::get_travel_cost(char terType){
	int travel_cost = 0;

	switch(terType){
		case '~': //water
			travel_cost = 0;
			break;
		case '=': //wall
			travel_cost = -1;
			break;
		case '.': //meadow
			travel_cost = -1;
			break;
		case '"': //swamp
			travel_cost = -2;
			break;
		default:	
			break;
	}
	return travel_cost;
}

//displays information about certain terrain type in menu section of screen
//terrain type passed in as character representation
bool terrain::display_info(char terType){
	int row = 4;   	//change this variable to move the position of the text up or down
	int offset  = 5;    //change this to move it right or left
	clearLines(row);
	switch(terType){
		case '~': //water
      displayStat(row, "Water: ", offset);
      displayStat(row, "Cost: 0 energy", offset);
      displayStat(row, "A Boat is required", offset);
			break;
		case '=': //wall
      displayStat(row, "Wall: ", offset);
      displayStat(row, "Cost: -1 energy", offset);
      displayStat(row, "Impassable", offset);
			break;
		case '.': //meadow
      displayStat(row, "Meadow: ", offset);
      displayStat(row, "Cost: -1 energy", offset);
			break;
		case '"': //swamp
      displayStat(row, "Swamp: ", offset);
      displayStat(row, "Cost: -2 energy", offset);
			break;
		default:
			break;
	}
	refresh();
	return true;
}
