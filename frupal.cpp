#include "frupal.h"

Frupal::Frupal(WINDOW * win, int y, int x)
{
  curWin = win;

	xHero = x;
	yHero = y;
	mvwaddch(curWin, yHero, xHero, '@');

  xCur = x;
  yCur = y;
  xMax = yMax = 128;

  keypad(curWin, true);

  mainGuy = Hero(1000, 100);
  //Talked to bart - dynamic map size is unncecessary.
  //Made static.
  for(int i = 0; i < yMax; ++i)
    for(int j = 0; j < xMax; ++j)
    {
      terrainMap[i][j] = '.';
      visitMap[i][j] = false;
    }	    
  
  loadFinished = true;
}

//constructor with file
Frupal::Frupal(WINDOW * win, char * mapFileName): xHero(5), yHero(5)//remove
{
  curWin = win;
  keypad(curWin, true);
  mainGuy = Hero(1000, 100);

	wbkgd(win, COLOR_PAIR(6));

  loadFinished = loadMap(mapFileName);
  if(loadFinished)
	  mvwaddch(curWin, yHero, xHero, '@');
}

//Load game state from map file. Returns boolean success/fail.
bool Frupal::loadMap(char * mapFileName)
{
  ifstream mapFile(mapFileName);
  if(!mapFile)
    return false;

  //Check whether this file claims to be a map we understand
  string elemName;
  mapFile >> elemName;
  if(elemName.compare("Frupal_Kingdom:") != 0)
    return false;

  if(mapFile.fail())
    return false;

  bool foundTerrain = false;
  bool foundStart= false;
  bool foundDiamonds= false;
  bool lastParseOK = true;


  // Attempts to use mapFile.fail(), .bad(), and .eof() to detect read / parse failures weren't working.
  // Most tests passed OK, however using getline() to read the end of the last line of text in the mapfile
  // would set the fail() bit, even if there was a newline (or several newlines) following the last element
  // description. It worked OK if there was another element that didn't have arbitrary length text at it's
  // end (like ship or diamonds) on the final line, as those elements use >> instead of getline() for their
  // last read operation.
  //
  // Researching  >> and getline() lead me to:
  // https://gehrcke.de/2011/06/reading-files-in-c-using-ifstream-dealing-correctly-with-badbit-failbit-eofbit-and-perror/
  // I'm going to try the 'get a line and parse it' pattern they suggest instead, with adaptations for 
  // handling the multiline terrain: element and other frupal specific sanity checks. -- JTN
  string sourceLine;
  while(getline(mapFile,sourceLine) && lastParseOK) {
    lastParseOK = parseLine(sourceLine, mapFile, foundTerrain, foundStart, foundDiamonds);  
  }

  return (foundTerrain && foundStart && foundDiamonds && lastParseOK);
}

//Parse most elements from a single line string
//Takes a reference to the mapFile stream so the terrain: element may read multiple lines
//Sets terrain, start, and diamonds booleans to true when those elements are found so that 
//the calling function can verify that these Required elements have been loaded.
bool Frupal::parseLine(string line, ifstream & mapFile, bool & terrain, bool & start, bool & diamonds)
{
  int x, y;
  string elemName;
  grovnik* newItem = NULL;

  if(line.length() == 0) //blank lines
    return true;
  if(line.length() == 1 && line[0] == '\r')
    return true;

  if(line[0] == '#') //Comments
    return true;

  stringstream lineStream(line);

  lineStream >> elemName;

  if(elemName.compare("terrain:") == 0) {
    lineStream >> xMax >> yMax;
    if(xMax < 1 || xMax > 128 || yMax < 1 || yMax > 128)
      return false;

    //Adjusted for static map size
    for(int i = 0; i < yMax; ++i){
      for(int j = 0; j < xMax; ++j){

        terrainMap[i][j] = mapFile.get();
        visitMap[i][j] = false;
      }
      mapFile.ignore(1000, '\n');
    }
    terrain = true;
  }
  else if(elemName.compare("start:") == 0) {
    lineStream >> xHero >> yHero;
    if(xHero < 0 || xHero >= xMax || yHero < 0 || yHero >= yMax) 
      return false;
    start = true;
  }
  else if (elemName.compare("diamonds:") == 0) {
    newItem = new royal_diamond();
    diamonds = true;
  }
  else if(elemName.compare("treasure:") == 0) {
    newItem = new treasure_chest();
  }
  else if(elemName.compare("food:") == 0) {
    newItem = new food();
  }
  else if(elemName.compare("clue:") == 0) {
    newItem = new clue();
  }
  else if(elemName.compare("ship:") == 0) {
    //TODO: implement
  }
  else if(elemName.compare("binoculars:") == 0) {
    //TODO: implement
  }
  else if(elemName.compare("obstacle:") == 0) {
    newItem = new obstacle();
  }
  else if(elemName.compare("tool:") == 0) {
    newItem = new tool();
  }


  if(newItem)
  {
    lineStream >> x >> y;
    if(x <0 || x >= xMax || y < 0 || y >= yMax)
      return false;
    lineStream >> *newItem;
    itemMap[y][x] = newItem;
  }

  return true;

}

bool Frupal::mapLoaded() { return loadFinished; }

Frupal::~Frupal()
{
}

//lk series updates cursors location coordinates for the map window, which will get updated in the disp() function

//lkup updates cursor location upwards
void Frupal::lkup()
{
  yCur -= 1;
  if(yCur < 1)
    yCur = yMax;
	wmove(curWin, yCur, xCur);
}

//lkdn updates cursor location downwards
void Frupal::lkdn()
{
  yCur -= -1; //yes, I am aware that this is...non-standard. lol
  if(yCur > yMax)
    yCur = 1;
	wmove(curWin, yCur, xCur);
}

//lklt updates cursor location to left
void Frupal::lklt()
{
  xCur -= 1;
  if(xCur < 1)
    xCur = xMax;
	wmove(curWin, yCur, xCur);
}

//lkrt updates cursor location to the right
void Frupal::lkrt()
{
  xCur -= -1;
  if(xCur > xMax)
    xCur = 1;
	wmove(curWin, yCur, xCur);
}

//mvup moves cahracter up
void Frupal::mvup(){
	if(validMove(yHero - 1, xHero)){
		mvwdelch(curWin, yHero, xHero);

		yHero -= 1;
		showMap();//update map

		if(!mainGuy.modEner(terrainInfo.get_travel_cost(terrainMap[yHero][xHero]))){
			loseGame();
		}
    //moving our hero now updates the cursor location to him
    yCur = yHero;
    xCur = xHero;
	}
}

//mvdn moves cahracter down
void Frupal::mvdn(){
	if(validMove(yHero + 1, xHero)){
		mvwdelch(curWin, yHero, xHero);

		yHero += 1;
		showMap();//update map
		
		if(!mainGuy.modEner(terrainInfo.get_travel_cost(terrainMap[yHero][xHero]))){
			loseGame();
		}
    //moving our hero now updates the cursor location to him
    yCur = yHero;
    xCur = xHero;
	}
}

//mvlt moves cahracter left
void Frupal::mvlt(){
	if(validMove(yHero, xHero - 1)){
		mvwdelch(curWin, yHero, xHero);

		xHero -= 1;
		showMap();//update map

		if(!mainGuy.modEner(terrainInfo.get_travel_cost(terrainMap[yHero][xHero]))){
			loseGame();
		}
    //moving our hero now updates the cursor location to him
    yCur = yHero;
    xCur = xHero;

	}
}

//mvrt moves cahracter right
void Frupal::mvrt(){
	if(validMove(yHero, xHero + 1)){
		mvwdelch(curWin, yHero, xHero);

		xHero += 1;
		showMap();//update map

		if(!mainGuy.modEner(terrainInfo.get_travel_cost(terrainMap[yHero][xHero]))){
			loseGame();
		}
    //moving our hero now updates the cursor location to him
    yCur = yHero;
    xCur = xHero;
	}
}

//checks if a move is valid
bool Frupal::validMove(int y, int x){
	//checks for out of bounds
	if(y < 0 || y >= yMax){
		return false;
	}else if(x < 0 || x >= xMax){
		return false;

	//checks for a wall
	}else if(terrainMap[y][x] == '='){
		if(!mainGuy.modEner(-1)){
			loseGame();
		}
		return false;

	//checks for water
	}else if(terrainMap[y][x] == '~'){
		if(mainGuy.checkInventory("ship")){
			return true;
		}
		return false;
	}

	return true;
}

//function displays loss and waits to exit game //TODO
void Frupal::loseGame(){
}

//function displays win and waits to exit game //TODO
void Frupal::winGame(){
}

//gets input from the user - currently only allows movement of cursor and character, and quitting. 
//If an incorrect key is received, it simply recursively calls itself and awaits input
int Frupal::getmv()
{
  int ch = wgetch(curWin);
  wattroff(curWin, A_REVERSE);
  switch(ch)
  {
    case KEY_UP://cursor up
      lkup();
      break;
    case KEY_DOWN://cursor down
      lkdn();
      break;
    case KEY_LEFT://cursor left
      lklt();
      break;
    case KEY_RIGHT://cursor right
      lkrt();
      break;
		case 'w'://hero up
			mvup();
			break;
		case 'a'://hero left
			mvlt();
			break;
		case 's': //hero down
			mvdn();
			break;
		case 'd'://hero right
			mvrt();
			break;
    case 'q':
      break;
    default:
      ch = getmv();
      break;
  }
    wrefresh(curWin);//refresh the window
  return ch;
}

void Frupal::updateVisitMap(){
  for(int y = yHero - 1; y <= yHero + 1; y++){
    for(int x = xHero - 1; x <= xHero + 1; x++){
			visitMap[y][x] = true;
		}
	}
}

//new show map function handles the color display, and updates
//the heros location when he moves, rather than having that
//occur in four separate functions
void Frupal::showMap()
{
	updateVisitMap();
  char grovnikIcon = ' ';
  grovnik * currentGrovnik;

	//updates map
	for(int y = 0; y < yMax; y++){
		for(int x = 0; x < xMax; x++){
			
			//discovered areas
			if(visitMap[y][x] == true){
				int color = terrainInfo.get_color(terrainMap[y][x]);//gets color

        //Display item grovniks
        currentGrovnik = itemMap[y][x];
        if(currentGrovnik){
          grovnikIcon = currentGrovnik->get_character();
          if(grovnikIcon == '%') { //special case the royal diamonds
            color = COLOR_PAIR(7); // white on cyan
            grovnikIcon = '$';
          }
        } else {
          grovnikIcon = ' '; //No item, show just the terrain.
        }

				wattron(curWin, color);//turn on color pair
				mvwaddch(curWin, y, x, grovnikIcon);//write space to map
				wattroff(curWin, color);//turn off color pair

			//undiscovered areas
			}else{ 
				wattron(curWin, COLOR_PAIR(6));//turn on color BLACK
				mvwaddch(curWin, y, x, ' ');//write space to map
				wattroff(curWin, COLOR_PAIR(6));//turn off color BLACK
			}
		}
	}

	//shows hero on screen
	wattron(curWin, COLOR_PAIR(1));//turn on color RED
	mvwaddch(curWin, yHero,xHero,'@');//write @ to map for hero
	wattroff(curWin, COLOR_PAIR(1));//turn off color RED
}
