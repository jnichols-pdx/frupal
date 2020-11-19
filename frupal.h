#include <ncurses.h>
#include <cmath>
#include <stdio.h>
#include <fstream>
#include <string>
#include <unistd.h>
#include "hero.h"
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
		void mvup();
		void mvdn();
		void mvlt();
		void mvrt();
  	bool updateVisitMap(int y, int x); //update discovered map		
		bool validMove(int y, int x);
		void loseGame();
		void winGame();
    bool loadMap(char * mapFileName);

    int xCur, yCur, xMax, yMax; //current, current, maximum, maximum
		int xHero, yHero;
    WINDOW * curWin;
    Hero mainGuy;
  	bool visitMap[128][128]; //map to track discovered places
		char terrainMap[128][128];
    bool loadFinished;
};

