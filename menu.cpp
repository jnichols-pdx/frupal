//Utility functions for the menu, needed by multiple classes
#include "menu.h"


//clears data on menu from start to end lines
void menu::clearLines(int start, int end){
  //If end isn't specified by the caller, default to 
  //clearing all lines from start to just above the Energy: display
  if(-1 == end)
  {
    int y = getmaxy(stdscr);
    end = y - 4;
  }

	if(start == end){return;}
	if(start > end){return;}
	
	int x = getmaxx(stdscr);
	
	move(start, x * .75 + 1);

	clrtoeol();
	clearLines(++start, end);	
}

void menu::displayStat(int & row, const char * text, int offset){
	if(!text){return;}

  int x = getmaxx(stdscr);
  int menu_width = (x - (x * .75)) - 1;
  int chunkMax = menu_width - offset;
  int textSize = strlen(text) ;
  int chunkPrinted = 0;


  move(row, x - menu_width + offset);
  for(int i = 0; i < textSize; ++i)
  {
    if(text[i] == '\n' || chunkPrinted >= chunkMax)
    {
      //move down! clean cups clean cups!
      ++row;
      chunkPrinted = 0;
      move(row, x - menu_width + offset);

      //Don't actually print the newline character, also skip
      //spaces if we wrapped to the next line at a space character
      if(text[i] != '\n' && text[i] != ' ') 
      {
        addch(text[i]);
        ++chunkPrinted;
      }
    }
    else
    {
      addch(text[i]);
      ++chunkPrinted;
    }
  }

  //displayStat inherently moves the cursor down to 
  //one row below the printed output.
  ++row;
}
