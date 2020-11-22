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
	//inventory[0] = new tool("ship");
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
bool Hero::checkInventory(char * item){
	if(item == NULL) return false;   //empty string return false

	for(int i=0; i<INVSIZE; ++i){
		if(inventory[i] == NULL) {}
		else{
			if(inventory[i]->check_equal(item) == true)
			return true;
		}
	}

	return false;
}
		
Hero::~Hero(){
	for(int i =0; i < INVSIZE; ++i){
		if(inventory[i] != NULL) delete inventory[i];
		else{}
	}
}
