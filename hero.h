#include "grovnik.h"

const int INVSIZE = 10;

class Hero
{
  public:
		Hero(); //Hero constructor
		Hero(int whif, int nRG); //Hero constructor
		~Hero();
		bool modEner(int nRG); //modify energy - adds by default. To lower energy, send in negative number
		bool modWhif(int whif); //modify whiffles - adds by default. To lower number of whiffles, send in negative number
		bool checkInventory(const char * item);	//check if the hero has this in their inventory, returns false when its not in it
		bool addTool(tool * item);  //returns false if inventory is full, unless a ship is being added it will add the ship
		bool selectTool(tool * & item);	//selects a tool and copies it into the item argument, returns false if inventory is empty
						//or if the hero selects the ship. The hero can not remove the ship from their inventory

  private:
  	int whiffles; //hero whiffles
  	int energy; //hero energy
	int items; //items in the inventory
        tool *inventory[INVSIZE+1];	//10 inventory items
};
