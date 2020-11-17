//Character class for Kingdom of Frupal

#include "hero.h"

Hero::Hero(){
	whiffles = 1000;
	energy = 100;
}

Hero::Hero(int whif, int nRG){
	whiffles = whif;
	energy = nRG;
}

void Hero::modEner(int nRG)
{
  energy += nRG;
}

void Hero::modWhif(int Whif)
{
  whiffles += Whif;
}
