#include <string>
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
	

  private:
  	int whiffles; //hero whiffles
  	int energy; //hero energy
        tool *inventory[INVSIZE+1];	//10 inventory items
};
