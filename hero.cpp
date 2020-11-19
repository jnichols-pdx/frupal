//Character class for Kingdom of Frupal

#include "hero.h"

Hero::Hero(){
	whiffles = 1000;
	energy = 100;
        for(int i = 0; i<10; ++i){
 		inventory[i] = NULL;	
	}
}

Hero::Hero(int whif, int nRG){
	whiffles = whif;
	energy = nRG;
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

//checks inventory for a certain item
bool Hero::checkInventory(const char * item){
	return true;
}
