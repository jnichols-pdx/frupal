//Character class for Kingdom of Frupal
#include "hero.h"

Hero::Hero(){
	whiffles = 1000;
	energy = 100;
        for(int i = 0; i<INVSIZE; ++i){
 		inventory[i] = NULL;	
	}
}

Hero::Hero(int whif, int nRG){
	whiffles = whif;
	energy = nRG;
        for(int i = 0; i<10; ++i){
 		inventory[i] = NULL;	
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

//checks inventory for a certain item
bool Hero::checkInventory(const char * item){
	if(item == NULL) return false;   //empty string return false
        char * temp;
	temp = new char[strlen(item)+1];
	strcpy(temp,item);

	for(int i=0; i<INVSIZE; ++i){
		if(inventory[i]->check_equal(temp) == true){
			delete [] temp;
			temp = NULL;
			return true;
		}
	}
	delete [] temp;
	temp = NULL;

	return false;
}
		
Hero::~Hero(){
	for(int i =0; i < INVSIZE; ++i){
		delete inventory[i];
	}
}

