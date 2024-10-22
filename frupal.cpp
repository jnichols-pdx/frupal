#include "frupal.h"
#include <unistd.h>

using namespace ::menu;

Frupal::Frupal(WINDOW *win, int y, int x) {
  curWin = win;

  getmaxyx(curWin, winYMax, winXMax);
  mvwaddch(curWin, yHero, xHero, '@');
  multy = multx = 0;
  xCur = winXMax / 2;
  yCur = winYMax / 2;
  xMax = yMax = 128;

  keypad(curWin, true);

  mainGuy = Hero(1000, 100);
  // Talked to bart - dynamic map size is unncecessary.
  // Made static.
  for (int i = 0; i < yMax; ++i)
    for (int j = 0; j < xMax; ++j) {
      terrainMap[i][j] = '.';
      visitMap[i][j] = false;
      itemMap[i][j] = NULL;
    }

  loadFinished = true;
}

// constructor with file
Frupal::Frupal(WINDOW *win, char *mapFileName)
    : xHero(5), yHero(5) // remove
{
  curWin = win;

  getmaxyx(curWin, winYMax, winXMax);
  keypad(curWin, true);
  mainGuy = Hero(1000, 100);
  mainGuy.showHeroInfo();
  multy = multx = 0;

  wbkgd(win, COLOR_PAIR(6));

  for (int i = 0; i < 128; ++i)
    for (int j = 0; j < 128; ++j) {
      itemMap[i][j] = NULL;
    }

  loadFinished = loadMap(mapFileName);
  if (loadFinished)
    mvwaddch(curWin, yHero, xHero, '@');
}

// Load game state from map file. Returns boolean success/fail.
bool Frupal::loadMap(char *mapFileName) {
  ifstream mapFile(mapFileName);
  if (!mapFile) {
    endwin();
    cerr << "Failed to load the map!" << endl;
    cerr << "Could not open " << mapFileName << endl;
    exit(-1);
  }

  // Check whether this file claims to be a map we understand
  string elemName;
  mapFile >> elemName;
  if (elemName.compare("Frupal_Kingdom:") != 0) {
    endwin();
    cerr << "Failed to load the map!" << endl;
    cerr << mapFileName << " does not appear to be a mapfile." << endl;
    cerr << "Kingdom of Frupal map files start with \"Frupal_Kingdom:\" on the "
            "first line."
         << endl;
    cerr << "Found >" << elemName << "< instead." << endl;
    exit(-1);
  }

  if (mapFile.fail()) {
    endwin();
    cerr << "Failed to load the map!" << endl;
    cerr << "Unable to read mapfile after header element." << endl;
    exit(-1);
  }

  bool foundTerrain = false;
  bool foundStart = false;
  bool foundDiamonds = false;
  bool lastParseOK = true;

  // Attempts to use mapFile.fail(), .bad(), and .eof() to detect read / parse
  // failures weren't working. Most tests passed OK, however using getline() to
  // read the end of the last line of text in the mapfile would set the fail()
  // bit, even if there was a newline (or several newlines) following the last
  // element description. It worked OK if there was another element that didn't
  // have arbitrary length text at it's end (like ship or diamonds) on the final
  // line, as those elements use >> instead of getline() for their last read
  // operation.
  //
  // Researching  >> and getline() lead me to:
  // https://gehrcke.de/2011/06/reading-files-in-c-using-ifstream-dealing-correctly-with-badbit-failbit-eofbit-and-perror/
  // I'm going to try the 'get a line and parse it' pattern they suggest
  // instead, with adaptations for handling the multiline terrain: element and
  // other frupal specific sanity checks. -- JTN
  string sourceLine;
  while (getline(mapFile, sourceLine) && lastParseOK) {
    lastParseOK =
        parseLine(sourceLine, mapFile, foundTerrain, foundStart, foundDiamonds);
  }

  if (!(foundTerrain && foundStart && foundDiamonds)) {
    endwin();
    cerr << "Failed to load the map!" << endl;

    if (!foundTerrain)
      cerr << "Map did not contain the \"terrain:\" element." << endl;

    if (!foundStart)
      cerr << "Map did not contain the \"start:\" element." << endl;

    if (!foundDiamonds)
      cerr << "Map did not contain the \"diamonds:\" element." << endl;

    exit(-1);
  } else
    return true;
}

// Parse most elements from a single line string
// Takes a reference to the mapFile stream so the terrain: element may read
// multiple lines Sets terrain, start, and diamonds booleans to true when those
// elements are found so that the calling function can verify that these
// Required elements have been loaded.
bool Frupal::parseLine(string line, ifstream &mapFile, bool &terrain,
                       bool &start, bool &diamonds) {
  int x = -1, y = -1;
  string elemName;
  grovnik *newItem = NULL;

  if (line.length() == 0) // blank lines
    return true;
  if (line.length() == 1 && line[0] == '\r')
    return true;

  if (line[0] == '#') // Comments
    return true;

  stringstream lineStream(line);

  lineStream >> elemName;

  if (elemName.compare("terrain:") == 0) {

    if (terrain) {
      endwin();
      cerr << "Failed to load the map!" << endl;
      cerr << "Found \"terrain:\" more than once in the map file." << endl;
      cerr << "\"terrain:\" may only be specified once." << endl;
      cerr << "Offending line in map file:" << endl;
      cerr << ">>>" << line << "<<<" << endl;
      exit(-1);
    }

    lineStream >> xMax >> yMax;
    // reject map if map size too large or small
    if (xMax < 2 || xMax > 128 || yMax < 2 || yMax > 128) {
      endwin();
      cerr << "Failed to load the map!" << endl;
      cerr << "Invalid or unsupported terrain size: " << xMax << " x " << yMax
           << endl;
      cerr << "Allowed range is 2 x 2 to 128 x 128" << endl;
      cerr << "Offending line in map file:" << endl;
      cerr << ">>>" << line << "<<<" << endl;
      exit(-1);
    }

    // Adjusted for static map size
    char c = ' ';
    for (int i = 0; i < yMax; ++i) {
      for (int j = 0; j < xMax; ++j) {

        c = mapFile.get();

        if (c != '.' && c != '~' && c != '"' && c != '=') {
          endwin();
          cerr << "Failed to load the map!" << endl;
          cerr << "Found a '" << c << "' character on terrain row " << i
               << " column " << j << endl;
          cerr << "Allowed terrain characters are . ~ \" =" << endl;
          exit(-1);
        }

        terrainMap[i][j] = c;
        visitMap[i][j] = false;
      }
      mapFile.ignore(1000, '\n');
    }
    terrain = true;
    return true;
  }

  if (!terrain) {
    endwin();
    cerr << "Failed to load the map!" << endl;
    cerr << "Found \"" << elemName << "\" before \"terrain:\" in the map file."
         << endl;
    cerr << "\"terrain:\" must be specified before all other elements, except "
            "\"Frupal_Kingdom:\"."
         << endl;
    cerr << "Offending line in map file:" << endl;
    cerr << ">>>" << line << "<<<" << endl;
    exit(-1);
  }

  if (elemName.compare("start:") == 0) {
    if (start) {
      endwin();
      cerr << "Failed to load the map!" << endl;
      cerr << "Found \"start:\" more than once in the map file." << endl;
      cerr << "\"start:\" may only be specified once." << endl;
      cerr << "Offending line in map file:" << endl;
      cerr << ">>>" << line << "<<<" << endl;
      exit(-1);
    }
    lineStream >> xHero >> yHero;

    // reject map if hero starts out of bounds
    if (xHero < 0 || xHero >= xMax || yHero < 0 || yHero >= yMax) {

      endwin();
      cerr << "Failed to load the map!" << endl;
      cerr << "Hero starting location out of range: " << xHero << "," << yHero
           << endl;
      cerr << "Allowed range is 0,0 to " << xMax << "," << yMax << endl;
      cerr << "Offending line in map file:" << endl;
      cerr << ">>>" << line << "<<<" << endl;
      exit(-1);
    }

    xCur = winXMax / 2;
    yCur = winYMax / 2;

    start = true;
  } else if (elemName.compare("diamonds:") == 0) {
    if (diamonds) {
      endwin();
      cerr << "Failed to load the map!" << endl;
      cerr << "Found \"diamonds:\" more than once in the map file." << endl;
      cerr << "\"diamonds:\" may only be specified once." << endl;
      cerr << "Offending line in map file:" << endl;
      cerr << ">>>" << line << "<<<" << endl;
      exit(-1);
    }
    newItem = new royal_diamond();
    diamonds = true;
  } else if (elemName.compare("treasure:") == 0) {
    newItem = new treasure_chest();
  } else if (elemName.compare("food:") == 0) {
    newItem = new food();
  } else if (elemName.compare("clue:") == 0) {
    newItem = new clue();
  } else if (elemName.compare("ship:") == 0) {
    newItem = new ship();
  } else if (elemName.compare("binoculars:") == 0) {
    newItem = new binocular();
  } else if (elemName.compare("obstacle:") == 0) {
    newItem = new obstacle();
  } else if (elemName.compare("tool:") == 0) {
    newItem = new tool();
  } else {
    // reject map file on unexpected input
    {
      endwin();
      cerr << "Failed to load the map!" << endl;
      cerr << "Found unkown element: " << elemName << endl;
      cerr << "Offending line in map file:" << endl;
      cerr << ">>>" << line << "<<<" << endl;
      exit(-1);
    }
  }

  if (newItem) {
    lineStream >> x >> y;
    // reject if grovnik out of bounds
    if (x < 0 || x >= xMax || y < 0 || y >= yMax) {
      endwin();
      cerr << "Failed to load the map!" << endl;
      cerr << elemName << " location is out of range: " << x << "," << y
           << endl;
      cerr << "Allowed range is 0,0 to " << xMax << "," << yMax << endl;
      cerr << "Offending line in map file:" << endl;
      cerr << ">>>" << line << "<<<" << endl;
      exit(-1);
    }

    // Prevent placing items on top of walls.
    if ('=' == terrainMap[y][x]) {
      endwin();
      cerr << "Failed to load the map!" << endl;
      cerr << "Items may not be placed on walls, as they would be inaccessible."
           << endl;
      cerr << "Offending line in map file:" << endl;
      cerr << ">>>" << line << "<<<" << endl;
      exit(-1);
    }

    // reject map file if multiple grovniks at the same location
    if (itemMap[y][x] != NULL) {
      endwin();
      cerr << "Failed to load the map!" << endl;
      cerr << "Item location is already in use: " << x << "," << y << endl;
      cerr << "Offending line in map file:" << endl;
      cerr << ">>>" << line << "<<<" << endl;
      exit(-1);
    }

    try {
      lineStream >> *newItem;
    } catch (const char *s) {
      endwin();
      cerr << "Failed to load the map!" << endl;
      cerr << s << endl;
      cerr << "Offending line in map file:" << endl;
      cerr << ">>>" << line << "<<<" << endl;
      exit(-1);
    }

    itemMap[y][x] = newItem;
  }

  return true;
}

bool Frupal::mapLoaded() { return loadFinished; }

Frupal::~Frupal() {
  for (int y = 0; y < 128; y++) {
    for (int x = 0; x < 128; x++) {
      if (itemMap[y][x]) {
        delete itemMap[y][x];
      }
    }
  }
}

// lk series updates cursors location coordinates for the map window, which will
// get updated in the disp() function

// lkup updates cursor location upwards
void Frupal::lkup() {
  yCur -= 1;
  if (yCur < 0)
    yCur = 0;
  else if (yCur >= winYMax)
    yCur = winYMax - 1;
  curs_set(1); // Display cursor when it moves
  wmove(curWin, yCur, xCur);
}

// lkdn updates cursor location downwards
void Frupal::lkdn() {
  yCur -= -1; // yes, I am aware that this is...non-standard. lol
  if (yCur < 0)
    yCur = 0;
  else if (yCur >= winYMax)
    yCur = winYMax - 1;
  curs_set(1); // Display cursor when it moves
  wmove(curWin, yCur, xCur);
}

// lklt updates cursor location to left
void Frupal::lklt() {
  xCur -= 1;
  if (xCur < 0)
    xCur = 0;
  else if (xCur >= winXMax)
    xCur = xMax - 1;
  curs_set(1); // Display cursor when it moves
  wmove(curWin, yCur, xCur);
}

void Frupal::lkrt() {
  xCur -= -1;
  if (xCur < 0)
    xCur = 0;
  else if (xCur >= winXMax)
    xCur = winXMax - 1;
  curs_set(1); // Display cursor when it moves
  wmove(curWin, yCur, xCur);
}

// moves character by offsets passed in
char Frupal::heroMove(int yOffset, int xOffset) {
  // Clear cursor highlight info or messages like 'breaking obstacle' when next
  // we move.
  menu::clearLines(4);
  char status = validMove(yHero + yOffset, xHero + xOffset);
  if (status == ' ') { // valid move

    yHero += yOffset;
    xHero += xOffset;

    showMap(); // update map

    if (!mainGuy.modEner(
            terrainInfo.get_travel_cost(terrainMap[yHero][xHero]))) {
      return loseGame();
    }

    // moving our hero now updates the cursor location to him
    yCur = winYMax / 2;
    xCur = winXMax / 2;

    // And hides the cursor
    curs_set(0);
  }

  mainGuy.showHeroInfo();
  return status;
}

// Checks if a move is valid
char Frupal::validMove(int y, int x) {
  // Checks for out of bounds
  if (y < 0 || y >= yMax) {
    return 'n';
  } else if (x < 0 || x >= xMax) {
    return 'n';

    // Checks for a wall
  } else if (terrainMap[y][x] == '=') {
    if (!mainGuy.modEner(-1)) {
      return loseGame();
    }
    return 'n';

    // Checks for water
  } else if (terrainMap[y][x] == '~') {
    if (mainGuy.checkInventory("ship")) {
      int menuRow = (rand() % 2) + 4;
      menu::clearLines(3);
      menu::displayStat(menuRow, "v^v^ W~~A~~V~~E ^v^v");
      // Don't immediately return if we have a ship,
      // This allows us to interact with items that are on water.
    } else {
      if (!mainGuy.modEner(-1)) {
        return loseGame();
      }
      return 'n';
    }
  }

  if (itemMap[y][x]) {
    food *foodptr = dynamic_cast<food *>(itemMap[y][x]);
    if (foodptr) {
      if (mainGuy.purchaseItem(foodptr) == true) {
        refresh();
        delete itemMap[y][x];
        itemMap[y][x] = NULL;
      }
      refresh();
      foodptr = NULL;
      return ' ';
    }

    tool *toolptr = dynamic_cast<tool *>(itemMap[y][x]);
    if (toolptr) {
      if (mainGuy.purchaseItem(toolptr) == true) {
        refresh();
        delete itemMap[y][x];
        itemMap[y][x] = NULL;
      }

      refresh();
      toolptr = NULL;
      return ' ';
    }

    binocular *binocptr = dynamic_cast<binocular *>(itemMap[y][x]);
    if (binocptr) {
      if (mainGuy.purchaseItem(binocptr) == true) {
        delete itemMap[y][x];
        itemMap[y][x] = NULL;
      }

      binocptr = NULL;
      return ' ';
    }

    ship *shipptr = dynamic_cast<ship *>(itemMap[y][x]);
    if (shipptr) {
      if (mainGuy.purchaseItem(shipptr) == true) {
        delete itemMap[y][x];
        itemMap[y][x] = NULL;
      }

      binocptr = NULL;
      return ' ';
    }

    clue *clueptr = dynamic_cast<clue *>(itemMap[y][x]);
    if (clueptr) {
      clueptr->discover();
      clueptr->display_info();
      return ' ';
    }

    treasure_chest *treasureptr = dynamic_cast<treasure_chest *>(itemMap[y][x]);
    if (treasureptr) {
      treasureptr->discover();
      treasureptr->display_info();
      if (mainGuy.modWhif(treasureptr->get_amount())) {
        delete itemMap[y][x];
        itemMap[y][x] = NULL;
      }
      refresh();
      return ' ';
    }

    obstacle *obstacleptr = dynamic_cast<obstacle *>(itemMap[y][x]);
    if (obstacleptr) {
      char status = breakObstacle(obstacleptr, y, x);
      obstacleptr = NULL;
      return status;
    }

    royal_diamond *diamondptr = dynamic_cast<royal_diamond *>(itemMap[y][x]);
    if (diamondptr) {
      return winGame();
    }
  }

  return ' ';
}

// breaks obstacle at coordinates
char Frupal::breakObstacle(obstacle *item, int y, int x) {

  tool *copy = NULL;
  char status = ' ';

  int menuRow = item->display_info(); // displays obstacle info

  // no tool selected
  if (!mainGuy.selectTool(copy, item->get_kind_int(), menuRow)) {
    if (!mainGuy.modEner(item->get_b_energy())) {
      status = loseGame();

    } else {
      delete itemMap[y][x];
      itemMap[y][x] = NULL;
    }

  } else { // tool selected
    if (!mainGuy.modEner(item->get_b_energy() / copy->get_divisor())) {
      status = loseGame();

    } else {
      delete itemMap[y][x];
      itemMap[y][x] = NULL;
    }
  }

  if (copy != NULL) { // deallocate the copy
    delete copy;
    copy = NULL;
  }
  item = NULL;

  ++menuRow;
  menu::displayStat(menuRow, "! BREAKING \nOBSTACLE !");

  return status;
}

// function displays loss and waits to exit game
char Frupal::loseGame() {

  mainGuy.showHeroInfo();

  char ch = ' ';
  int pretty = 1;
  nodelay(curWin, true);
  while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N' && ch != 'q' &&
         ch != 'Q') {
    if (pretty > 1)
      pretty = 0;

    werase(curWin);
    wbkgd(curWin, COLOR_PAIR(10));
    wattron(curWin, COLOR_PAIR(9 + pretty));
    mvwaddstr(curWin, winYMax / 2, (winXMax / 2) - 5, "GAME OVER!");
    wattroff(curWin, COLOR_PAIR(9 + pretty));
    wattron(curWin, COLOR_PAIR(9 + pretty));
    mvwaddstr(curWin, winYMax / 2 + 1, (winXMax / 2) - 8, "Play Again (Y/N)");
    wattroff(curWin, COLOR_PAIR(9 + pretty));
    ch = wgetch(curWin);
    ++pretty;
    usleep(175000);
  }
  nodelay(curWin, false);
  if (ch == 'n' || ch == 'N' || ch == 'q' || ch == 'Q') {
    return 'q';
  }
  return 'r';
}

// function displays win and waits to exit game
char Frupal::winGame() {

  mainGuy.modWhif(999990000);
  mainGuy.showHeroInfo();
  char ch = ' ';
  int pretty = 0;
  nodelay(curWin, true);
  while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N' && ch != 'q' &&
         ch != 'Q') {
    if (pretty > 1)
      pretty = 0;

    werase(curWin);
    wbkgd(curWin, COLOR_PAIR(7));
    wattron(curWin, COLOR_PAIR(7 + pretty));
    mvwaddstr(curWin, winYMax / 2, (winXMax / 2) - 8, "A WINNER IS YOU!");
    wattroff(curWin, COLOR_PAIR(7 + pretty));
    wattron(curWin, COLOR_PAIR(7 + pretty));
    mvwaddstr(curWin, winYMax / 2 + 1, (winXMax / 2) - 8, "Play Again (Y/N)");
    wattroff(curWin, COLOR_PAIR(7 + pretty));
    ch = wgetch(curWin);
    ++pretty;
    usleep(175000);
  }
  nodelay(curWin, false);
  if (ch == 'n' || ch == 'N' || ch == 'q' || ch == 'Q') {
    return 'q';
  }
  return 'r';
}

// gets input from the user - currently only allows movement of cursor and
// character, and quitting. If an incorrect key is received, it simply
// recursively calls itself and awaits input
int Frupal::getmv() {

  int ch = wgetch(curWin);
  wattroff(curWin, A_REVERSE);
  switch (ch) {
  case KEY_UP: // cursor up
    lkup();
    showCurInfo(yCur, xCur);
    break;
  case KEY_DOWN: // cursor down
    lkdn();
    showCurInfo(yCur, xCur);
    break;
  case KEY_LEFT: // cursor left
    lklt();
    showCurInfo(yCur, xCur);
    break;
  case KEY_RIGHT: // cursor right
    lkrt();
    showCurInfo(yCur, xCur);
    break;
  case 'w': // hero up
    ch = heroMove(-1, 0);
    break;
  case 'a': // hero left
    ch = heroMove(0, -1);
    break;
  case 's': // hero down
    ch = heroMove(1, 0);
    break;
  case 'd': // hero right
    ch = heroMove(0, 1);
    break;
  case 'q':
    break;
  default:
    ch = getmv();
    break;
  }
  wrefresh(curWin); // refresh the window
  return ch;
}

void Frupal::updateVisitMap() {
  int range = mainGuy.visionRange();
  for (int y = yHero - range; y <= yHero + range; y++) {
    for (int x = xHero - range; x <= xHero + range; x++) {
      if (y >= 0 && y < 128 && x >= 0 && x < 128)
        visitMap[y][x] = true;
    }
  }
}

void Frupal::updateCur() {
  if (yHero >= winYMax * (multy + 1)) {
    ++multy;
  } else if (yHero < winYMax * (multy) && (multy - 1) >= 0) {
    --multy;
  } else if (xHero >= winXMax * (multx + 1)) {
    ++multx;
  } else if (xHero < winXMax * (multx) && (multx - 1) >= 0) {
    --multx;
  }
}

// new show map function handles the color display, and updates
// the heros location when he moves, rather than having that
// occur in four separate functions
void Frupal::showMap() {
  updateVisitMap();
  char grovnikIcon = ' ';
  grovnik *currentGrovnik;

  werase(curWin);

  updateCur();

  // updates map
  for (int y = 0; y < yMax; y++) {
    for (int x = 0; x < xMax; x++) {
      // discovered areas
      if (visitMap[y][x] == true) {
        int color = terrainInfo.get_color(terrainMap[y][x]); // gets color
        // Display item grovniks
        currentGrovnik = itemMap[y][x];

        if (currentGrovnik) {
          grovnikIcon = currentGrovnik->get_character();
          if (grovnikIcon == '%') { // special case the royal diamonds
            color = COLOR_PAIR(7);  // white on cyan
            grovnikIcon = '$';
          }
        } else {
          grovnikIcon = ' '; // No item, show just the terrain.
        }

        wattron(curWin, color); // turn on color pair
        mvwaddch(curWin, y + (winYMax / 2) - yHero, x + (winXMax / 2) - xHero,
                 grovnikIcon);   // write space to map
        wattroff(curWin, color); // turn off color pair
        // undiscovered areas
      } else {
        wattron(curWin, COLOR_PAIR(6)); // turn on color BLACK
        mvwaddch(curWin, y + (winYMax / 2) - yHero, x + (winXMax / 2) - xHero,
                 ' ');                   // write space to map
        wattroff(curWin, COLOR_PAIR(6)); // turn off color BLACK
      }

      // Unfinished addition of # border around playable map area
      // if(((y == (winYMax/2)-yHero-1) && x >= (winXMax/2)-xHero-1 && x <=
      // (winXMax/2)+xHero+1) || (y >= (winYMax/2)-yHero-1 && y <=
      // (winXMax/2)+yHero+1 && x == (winXMax/2)-xHero-1))
      // mvwaddch(curWin,y,x,'#');
    }
  }

  // shows hero on screen
  wattron(curWin, COLOR_PAIR(1));                  // turn on color RED
  mvwaddch(curWin, winYMax / 2, winXMax / 2, '@'); // write @ to map for hero
  wattroff(curWin, COLOR_PAIR(1));                 // turn off color RED
}

// shows information on current cursor coordinate
int Frupal::showCurInfo(int y, int x) {
  int trueY = y - (winYMax / 2) + yHero;
  int trueX = x - (winXMax / 2) + xHero;
  if (trueY >= 0 && trueY < yMax && trueX >= 0 && trueX < xMax) {
    grovnik *currentGrovnik = itemMap[trueY][trueX];

    // displays cursor info if on discovered tile

    if (visitMap[trueY][trueX]) {
      if (currentGrovnik) {
        return currentGrovnik
            ->display_info(); // if theres a grovnik, display info
      }

      // otherwise it displays terrain info
      terrainInfo.display_info(terrainMap[trueY][trueX]);
      return 7;
    }
  }

  terrainInfo.display_info('0');
  int row = 4;
  displayStat(row, "Darkness rules here", 3);
  refresh();
  return 5;
}
