#include <ncurses.h>
#include <cmath>
#include <stdio.h>
#include <unistd.h>
#include "hero.h"
#include "grovnik.h"

using namespace std;

class Frupal
{
  public:
    Frupal(WINDOW * win, int y, int x);
		~Frupal();
    int  getmv(); //move cursor
    void lkup();  //move cursor up
    void lkdn();  //move cursor down
    void lklt();  //move cursor left
    void lkrt();  //move cursor right
    void disp();  //display
  	bool updateVisitMap(int y, int x); //update discovered map
  private:
    int xCur, yCur, xMax, yMax; //current, current, maximum, maximum
    WINDOW * curWin;
    Hero * mainGuy;
  	bool visitMap[128][128]; //map to track discovered places
};

