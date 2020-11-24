//source code for terrain classes

#include "terrain.h"

terrain::terrain(){}

terrain::~terrain(){}

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
	int y = 4;   	//change this variable to move the position of the text up or down
	int x = 5;    //change this to move it right or left

	clearLines(y);

	switch(terType){
		case '~': //water
			mvwprintw(stdscr, y, COLS*0.75+x, "Water: ");
			mvwprintw(stdscr, y+1, COLS*0.75+x, "Cost to move through is 0 energy");
			mvwprintw(stdscr, y+2, COLS*0.75+x, "A Boat is required to move through      ");
			break;
		case '=': //wall
			mvwprintw(stdscr, y, COLS*0.75+x, "Wall: ");
			mvwprintw(stdscr, y+1, COLS*0.75+x, "You can't pass through                ");
			mvwprintw(stdscr, y+2, COLS*0.75+x, "An attempt to do so will cost 1 energy");
			break;
		case '.': //meadow
			mvwprintw(stdscr, y, COLS*0.75+x, "Meadow: ");
			mvwprintw(stdscr, y+1, COLS*0.75+x, "Cost to move through is 1 energy");
			break;
		case '"': //swamp
			mvwprintw(stdscr, y, COLS*0.75+x, "Swamp: ");
			mvwprintw(stdscr, y+1, COLS*0.75+x, "Cost to move through is 2 energy");
			break;
		default:
			break;
	}
	refresh();
	return true;
}

void terrain::clearLines(int start, int end){
	if(start == end){return;}
	if(start > end){return;}

	int x = getmaxx(stdscr);
	move(start, x * .75 + 1);

	clrtoeol();
	clearLines(++start, end);	
}
