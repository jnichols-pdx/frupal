//Character class for Kingdom of Frupal

#include "hero.h"

Hero::Hero(){
	whiffles = 1000;
	energy = 100;
        for(int i = 0; i<INVSIZE; ++i){
 		inventory[i] = NULL;	
	}
	items = 0;
}

Hero::Hero(int whif, int nRG){
	whiffles = whif;
	energy = nRG;
	items = 0;
        for(int i = 0; i<10; ++i){
 		inventory[i] = NULL;	
	}	
	//inventory[0] = new tool("ship");
}

Hero::~Hero(){
	for(int i =0; i < INVSIZE; ++i){
		if(inventory[i] != NULL) delete inventory[i];
		else{}
	}
}

bool Hero::modEner(int nRG)
{
  energy += nRG;

	if(energy <= 0){
		return false;
	}

	return true;
}

bool Hero::modWhif(int whif)
{
	if(whiffles += whif < 0){
		return false;
	}

  whiffles += whif;
	return true;
}

int Hero::getEner(){
	return energy;
}

int Hero::getWhif(){
	return whiffles;
}

//checks inventory for a certain item
bool Hero::checkInventory(const char * item){
	if(item == NULL) return false;   //empty string return false

	for(int i=0; i<INVSIZE; ++i){
		if(inventory[i] == NULL) {}	//for no seg faults
		else{
			if(inventory[i]->check_equal(item) == true)
			return true;
		}
	}

	return false;
}

bool Hero::addTool(tool * item){  //returns false if inventory is full, unless a ship is being added it will add the ship
	if(item == NULL) return false;
	if(item->check_equal("ship") ==  true){		//if we are adding the ship
		for(int i=0; i<INVSIZE; ++i){		//first check if theres space available
			if(inventory[i] == NULL) {
				inventory[i] = new tool(*item);		//copy item into inventory
				whiffles = whiffles - item->get_cost();
				++items;
				return true;
			}
		}
		delete inventory[0];			//there wasn't space, free space and add. 
							//element 0 is just a placeholder
							//we can discuss where we want to place the ship
		inventory[0] = new tool(*item);		
		whiffles = whiffles - item->get_cost();
		return true;
	}
	else{
		for(int i=0; i<INVSIZE; ++i){
			if(inventory[i] == NULL) {		//theres space add here
				inventory[i] = new tool(*item);		
				whiffles = whiffles - item->get_cost();
				++items;
				return true;
			}
		}
	}
	
	return false;	//inventory was full
}
		
bool Hero::selectTool(tool * & item){	//selects a tool and copies it into the item argument, returns false if inventory is empty
	if(item != NULL){
		delete item;
		item = NULL;	
	}
	if(items == 0) return false;  //empty inventory

	keypad(stdscr, true);
	
	int y = 10;	//where the inventory starts in the menu
	int arrPos = 0; //array position
	int userInput = 0;
	mvwprintw(stdscr, y+items+1, COLS*0.75+3, "Select tool by pressing RETURN");	//not sure why this doesn't work
	mvwprintw(stdscr, y+items+2, COLS*0.75+3, "The tool 'ship' is unselectable");

	for(int i=0; i<items;++i){//display everything in inventory
		inventory[i]->display_name(i+y);		
	}
	refresh();
	do{	
		mvwprintw(stdscr, y+arrPos, COLS*0.75+2, ">");	//highlight new position
		refresh();
		userInput = getch();
		switch(userInput){
			case KEY_UP:
				if(arrPos == 0){		//if at first element
					mvwprintw(stdscr, y+arrPos, COLS*0.75+2, " ");	//clear current one	//the > display and moving does not work
					arrPos = items -1; //go to last element
					mvwprintw(stdscr, y+arrPos, COLS*0.75+2, ">");	//highlight new position
					refresh();
				}
				else{
					mvwprintw(stdscr, y+arrPos, COLS*0.75+2, " ");
					--arrPos;
					mvwprintw(stdscr, y+arrPos, COLS*0.75+2, ">"); 
					refresh();
				}
				break;
	
			case KEY_DOWN:
				if(arrPos == items -1){ 	//if at last element
					mvwprintw(stdscr, y+arrPos, COLS*0.75+2, " ");	//clear current one
					arrPos = 0; //go to first element
					mvwprintw(stdscr, y+arrPos, COLS*0.75+2, ">");	//highlight new position
					refresh();
				}
				else{
					mvwprintw(stdscr, y+arrPos, COLS*0.75+2, " ");
					++arrPos;
					mvwprintw(stdscr, y+arrPos, COLS*0.75+2, ">"); 
					refresh();
				}
				break;
			default: break;	
		}
		refresh();
	}while(userInput != char(10));

	if(inventory[arrPos]->check_equal("ship") == true) return false; //can't remove the ship

	for(int i = 0; i< INVSIZE+2;++i){		//clear inventory in menu				//this works
		mvwprintw(stdscr, y+i, COLS*0.75+2, "                                         ");
	}
	refresh();

	item = new tool(*inventory[arrPos]);	//copy tool item with copy constructor
	delete inventory[arrPos];		//deallocate memory
	
	for(int i = arrPos; i <items; ++i){	//shift everything up
		if(i == items -1){		//if at last element
			inventory[i] = NULL;
			--items;
			return true;
		}
		inventory[i] = inventory[i+1];
	}

	return false;
}
