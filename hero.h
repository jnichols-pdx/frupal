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
<<<<<<< HEAD
		int getEner();
		int getWhif();
		void displayStats();
		bool checkInventory(char * item);
	
=======
		bool checkInventory(const char * item);	//check if the hero has this in their inventory, returns false when its not in it
		bool addTool(tool * item);  //returns false if inventory is full, unless a ship is being added it will add the ship
		bool selectTool(tool * & item);	//selects a tool and copies it into the item argument, returns false if inventory is empty
						//or if the hero selects the ship. The hero can not remove the ship from their inventory
>>>>>>> 259dde2c1c347c1e4107afa0faf1ffa17c19c585

  private:
  	int whiffles; //hero whiffles
  	int energy; //hero energy
<<<<<<< HEAD
		tool *inventory[INVSIZE+1];	//10 inventory items
=======
	int items; //items in the inventory
        tool *inventory[INVSIZE+1];	//10 inventory items
>>>>>>> 259dde2c1c347c1e4107afa0faf1ffa17c19c585
};
