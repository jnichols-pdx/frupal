#include <ncurses.h>
#include <cmath>
#include <stdio.h>
#include <unistd.h>

using namespace std;

class Hero
{
  public:
  Hero(int whif, int nRG); //Hero constructor
  void modEner(int nRG); //modify energy - adds by default. To lower energy, send in negative number
  void modWhif(int Whif); //modify whiffles - adds by default. To lower number of whiffles, send in negative number
  bool updateMap(int y, int x); //update discovered map
  private:
  int whiffles; //hero whiffles
  int energy; //hero energy
  bool visitMap[128][128]; //map to track discovered places
};

class Frupal
{
  public:
    Frupal(WINDOW * win, int y, int x);
    int  getmv(); //move cursor
    void lkup();  //move cursor up
    void lkdn();  //move cursor down
    void lklt();  //move cursor left
    void lkrt();  //move cursor right
    void disp();  //display
  private:
    int xCur, yCur, xMax, yMax; //current, current, maximum, maximum
    WINDOW * curWin;
    Hero * mainGuy;
};

