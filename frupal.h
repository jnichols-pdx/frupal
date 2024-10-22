#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <random>
#include <sstream>
#include <string>

#include "grovnik.h"
#include "hero.h"
#include "menu.h"
#include "terrain.h"

using namespace std;

class Frupal {
public:
  Frupal(WINDOW *win, int y, int x);
  Frupal(WINDOW *win, char *mapFileName);
  ~Frupal();
  int getmv(); // move cursor
  bool mapLoaded();
  void showMap();

private:
  void lkup();      // cursor moves up
  void lkdn();      // cursor moves down
  void lklt();      // cursor moves left
  void lkrt();      // cursor moves right
  void updateCur(); // updates curMin and curMax series ints based on hero
                    // location - for map scroll

  char heroMove(int yOffset, int xOffset); // move hero by offsets
  char validMove(int y, int x);            // validates move

  void updateVisitMap(); // updates visible areas
  int showCurInfo(int y, int x);

  char loseGame(); // called when player runs out of energy
  char winGame();  // called when player gets royal diamond

  // breaks obstacle at coordinates
  char breakObstacle(obstacle *item, int y, int x);

  bool loadMap(char *mapFileName); // loads map from a filename

  // Parse one line/element
  bool parseLine(string line, ifstream &mapFile, bool &terrain, bool &start,
                 bool &diamonds);

  bool loadFinished;
  WINDOW *curWin; // ncurses window
  int xCur, yCur, xMax,
      yMax; // current map location for x and y, maximum map size x and y
  int winYMax, winXMax, multx, multy;
  // Above integers are: maximum size of window x and y, current minimum value
  // for x and y based on hero location, current maximum value for x and y based
  // on current hero location

  int xHero, yHero; // hero location
  Hero mainGuy;

  // map that holds items such as clues, food, tools etc.
  grovnik *itemMap[128][128];

  bool visitMap[128][128];   // map to track discovered places
  char terrainMap[128][128]; // map that holds terrain
  terrain terrainInfo;       // terrain info object
};
