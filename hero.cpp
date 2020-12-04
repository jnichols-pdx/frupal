//Character class for Kingdom of Frupal

#include "hero.h"

using namespace::menu;

Hero::Hero(){
	whiffles = 1000;
	energy = 100;
        for(int i = 0; i<INVSIZE; ++i){
 		inventory[i] = NULL;	
	}
	items = 0;
  vision = 1;
  waterWalk = false;
}

Hero::Hero(int whif, int nRG, int range){
	whiffles = whif;
	energy = nRG;
	items = 0;
        for(int i = 0; i<10; ++i){
 		inventory[i] = NULL;	
	}
  vision = range;
	//inventory[0] = new tool("ship");
  waterWalk = false;
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
  return energy > 0;
}

bool Hero::modWhif(int whif)
{
	if(whiffles + whif < 0){
		return false;
	}

  whiffles += whif;
	return true;
}

void Hero::showHeroInfo(){
	int xMax, yMax = 0;
	int offset = 2;
	int y, x = 0;
	char energyStr[5] = {0}; //game can support 9999 energy
	char whiffStr[10] = {0}; //game can support 999,999,999 whiffles

	getmaxyx(stdscr, yMax, xMax);

	move(yMax - 3, (xMax * viewPortRatio) + offset);
	clrtoeol(); 
	move(yMax - 2, (xMax * viewPortRatio) + offset);
	clrtoeol(); 

	mvprintw(yMax - 3, (xMax * viewPortRatio) + offset, "Energy: ");
	getyx(stdscr, y, x);
	sprintf(energyStr, "%d", energy);
	mvprintw(y, x, energyStr);

	mvprintw(yMax - 2, (xMax * viewPortRatio) + offset, "Whiffles: ");
	getyx(stdscr, y, x);
	sprintf(whiffStr, "%d", whiffles);
	mvprintw(y, x, whiffStr);

	refresh();
}

//Returns how far the hero can see.
int Hero::visionRange(){
  return vision;
}

//checks inventory for a certain item
bool Hero::checkInventory(const char * item){
	if(item == NULL) return false;   //empty string return false

//XXX quick and dirty check for ship, suggest refactoring.
  if(0 == strcmp(item,"ship"))
    return waterWalk;

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
				++items;
				return true;
			}
		}
	}
	
	return false;	//inventory was full
}
		
bool Hero::selectTool(tool * & item, int obstacleType, int menuRow){	//selects a tool and copies it into the item argument, returns false if inventory is empty
	if(item != NULL){
		delete item;
		item = NULL;	
	}
	if(items == 0) return false;  //empty inventory
			
	int counter = 0;
	keypad(stdscr, true);
	int startRow = menuRow;	//where the inventory starts in the menu      - change this variable to change y position of where inventory starts in the menu
	int arrPos = 0; //array position
	int userInput = 0;
	for(int i=0; i<items; ++i){
		if(inventory[i]->check_if_targets(obstacleType) == true) ++counter;	//check if there is no items in our inventory that can break the obstacle
	}
	if(counter == 0) return false;	//no items, return

	displayStat(menuRow, "Would you like to \nselect a tool? (Y/N)");
	refresh();
	userInput = getch();
	clearLines(startRow);
	refresh();
	if(userInput == 'N' || userInput == 'n') return false;

	displayStat(startRow, "Select tool by pressing RETURN");
	refresh();

	arrPos = select(obstacleType, menuRow + 2);	//which tool in inventory is selected
	clearLines(4);
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
    
int Hero::select(int obstacleType, int menuRow){
	int arrPos = 0;
	int userInput = 0;
	int startRow = menuRow;

	do{	
		if(userInput == char(10) && inventory[arrPos]->check_if_targets(obstacleType) == false){
			menuRow = startRow;
			clearLines(startRow);
			displayStat(menuRow, "You need to select a\ncorrect tool");		//this has a problem of displaying continuous lines after TODO
		}
		else{
			clearLines(startRow);
		}

		clearLines(startRow - 2, startRow);
		inventory[arrPos]->display_name(startRow - 2);		//display one at a time for simplicity sake
		
		refresh();
		userInput = getch();
		switch(userInput){
			case KEY_UP:
				if(arrPos == 0){		//if at first element
					arrPos = items -1; //go to last element
				}
				else{
					--arrPos;
				}
				break;
	
			case KEY_DOWN:
				if(arrPos == items -1){ 	//if at last element
					arrPos = 0; //go to first element
				}
				else{
					++arrPos;
				}
				break;
			default: break;	
		}
		refresh();
	}while((inventory[arrPos]->check_if_targets(obstacleType) == false) || userInput != char(10));     //continue to select until user makes valid decision
	return arrPos;

}


//asks the user if they want to buy an item, checks if its food or tools or binoculars
bool Hero::purchaseItem(grovnik * item){

	int row = item->display_info() + 1;
	displayStat(row, "Purchase? (Y/N)");
		
	int userInput = 0;
	userInput = getch();
		
	clearLines(4);

	//if hero purchases with 'y'
	if(userInput == 'y' || userInput == 'Y'){
		food * foodPtr = dynamic_cast<food*>(item);
		if(foodPtr){	//its food, time to eat
			
			//modifies whiffles and checks if hero can afford
			if(!this->modWhif(0 - foodPtr->get_cost())){
				displayStat(row, "Can't Afford It!");
				clearLines(row);
				foodPtr = NULL;
				return false;
			}

			//adds energy
			energy += foodPtr->get_energy();
			foodPtr = NULL;
			return true;
		}

		tool * toolPtr = dynamic_cast<tool*>(item);
		if(toolPtr){	//its a tool, add to inventory
			if(items == INVSIZE){ return false;}		//full inventory

			//modifies whiffles and checks if hero can afford
			if(!this->modWhif(0 - toolPtr->get_cost())){
				displayStat(row, "Can't Afford It!");
				clearLines(row);
				toolPtr = NULL;
				return false;
			}

			//adds tool to inventory
			if(addTool(toolPtr) == false){	//if something went wrong while adding to inventory
				toolPtr = NULL;
				return false;
			}

			toolPtr = NULL;	
			return true;	
		}

		binocular* binocPtr = dynamic_cast<binocular*>(item);
		if(binocPtr){	//its binoculars, improve hero's sight

			//modifies whiffles and checks if hero can afford
			if(!this->modWhif(0 - binocPtr->get_cost())){
				displayStat(row, "Can't Afford It!");
				clearLines(row);
				binocPtr = NULL;
				return false;
			}

      //increase vision range
			int range = binocPtr->get_range();
      if(vision < range) //don't downgrade if the user purchases another, worse, pair of binoculars
        vision = range;
			binocPtr = NULL;
			return true;
		}
    
		ship* shipPtr = dynamic_cast<ship*>(item);
		if(shipPtr){	//its a ship, give the hero waterWalk

			//modifies whiffles and checks if hero can afford
			if(!this->modWhif(0 - shipPtr->get_cost())){
				displayStat(row, "Can't Afford It!");
				clearLines(row);
				binocPtr = NULL;
				return false;
			}

      waterWalk = true;
			shipPtr= NULL;
			return true;
		}
	}

	clearLines(4);

	return false;
}
