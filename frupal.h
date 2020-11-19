#include <ncurses.h>
#include <cmath>
#include <stdio.h>
#include <fstream>
#include <string>
#include <unistd.h>
//#include "hero.h"
#include "terrain.h"

using namespace std;

class Frupal
{
  public:
    Frupal(WINDOW * win, int y, int x);
    Frupal(WINDOW * win, char * mapFileName);
		~Frupal();
    int  getmv(); //move cursor
    bool mapLoaded();	
    void showMap();
  private:

    void lkup();  //move cursor up
    void lkdn();  //move cursor down
    void lklt();  //move cursor left
    void lkrt();  //move cursor right
		void mvup(); //move hero up
		void mvdn(); //move hero down
		void mvlt(); //move hero left
		void mvrt(); //move hero right
		void updateVisitMap();
		bool validMove(int y, int x); //validates move
		void loseGame(); //called when player runs out of energy
		void winGame(); //called when player gets royal diamond
    bool loadMap(char * mapFileName); //loads map from a filename

    int xCur, yCur, xMax, yMax; //current, current, maximum, maximum
		int xHero, yHero; //hero location
    WINDOW * curWin; //ncurses window
    Hero mainGuy;
  	bool visitMap[128][128]; //map to track discovered places
		char terrainMap[128][128]; //map that holds terrain
		terrain terrainInfo; //terrain info object
    bool loadFinished;
};

