#include <string>
#include "grovnik.h"

class Hero
{
  public:
		Hero(); //Hero constructor
		Hero(int whif, int nRG); //Hero constructor
		bool modEner(int nRG); //modify energy - adds by default. To lower energy, send in negative number
		bool modWhif(int whif); //modify whiffles - adds by default. To lower number of whiffles, send in negative number
		bool checkInventory(const char * item);

  private:
  	int whiffles; //hero whiffles
  	int energy; //hero energy
        tool *inventory[11];
};
