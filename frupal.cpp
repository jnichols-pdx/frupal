#include "frupal.h"
#include <unistd.h>

Frupal::Frupal(WINDOW * win, int y, int x)
{
  curWin = win;

  getmaxyx(curWin, winYMax, winXMax);
	xHero = x;
	yHero = y;
	mvwaddch(curWin, yHero, xHero, '@');
  multy = multx = 0;
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
      itemMap[i][j] = NULL;
    }	    

  loadFinished = true;
}

//constructor with file
Frupal::Frupal(WINDOW * win, char * mapFileName): xHero(5), yHero(5)//remove
{
  curWin = win;

  getmaxyx(curWin, winYMax, winXMax);
  keypad(curWin, true);
  mainGuy = Hero(1000, 100);
	mainGuy.showHeroInfo();
  multy = multx = 0;

	wbkgd(win, COLOR_PAIR(6));

  for(int i = 0; i < 128; ++i)
    for(int j = 0; j < 128; ++j)
    {
      itemMap[i][j] = NULL;
    }

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
    //reject map if map size too large or small
    if(xMax < 2 || xMax > 128 || yMax < 2 || yMax > 128)
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
    //reject map if hero starts out of bounds
    if(xHero < 0 || xHero >= xMax || yHero < 0 || yHero >= yMax)
      return false;
    yCur = yHero;
    xCur = xHero;
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
    newItem = new ship();
  }
  else if(elemName.compare("binoculars:") == 0) {
    newItem = new binocular();
  }
  else if(elemName.compare("obstacle:") == 0) {
    newItem = new obstacle();
  }
  else if(elemName.compare("tool:") == 0) {
    newItem = new tool();
  }
  else {
    return false; //reject map file on unexpected input
  }


  if(newItem)
  {
    lineStream >> x >> y;
    if(x <0 || x >= xMax || y < 0 || y >= yMax) //reject if grovnik out of bounds
      return false;
    if(itemMap[y][x] != NULL)
      return false; //reject map file if multiple grovniks at the same location
    lineStream >> *newItem;
    itemMap[y][x] = newItem;
  }

  return true;

}

bool Frupal::mapLoaded() { return loadFinished; }

Frupal::~Frupal()
{
	for(int y = 0; y < 128; y++){
		for(int x = 0; x < 128; x++){
			if(itemMap[y][x]){
				delete itemMap[y][x];
			}
		}
	}
}

//lk series updates cursors location coordinates for the map window, which will get updated in the disp() function

//lkup updates cursor location upwards
void Frupal::lkup()
{
  yCur -= 1;
  if(yCur < (0 + (winYMax * multy)))
    yCur = ((multy + 1) * winYMax) -1;
  if(yCur >= yMax)
    yCur = yMax -1;
  curs_set(1); //Display cursor when it moves
	wmove(curWin, yCur % winYMax, xCur % winXMax);
}

//lkdn updates cursor location downwards
void Frupal::lkdn()
{
  yCur -= -1; //yes, I am aware that this is...non-standard. lol
  if(yCur >= ((multy+1)*winYMax) || yCur >= yMax)
    yCur = (multy * winYMax);
  curs_set(1); //Display cursor when it moves
	wmove(curWin, yCur % winYMax, xCur % winXMax);
}

//lklt updates cursor location to left
void Frupal::lklt()
{
  xCur -= 1;
  if(xCur < (0 + (winXMax * multx)))
    xCur = ((multx + 1) * winXMax) -1;
  if(xCur >= xMax)
    xCur = xMax -1;
  curs_set(1); //Display cursor when it moves
	wmove(curWin, yCur % winYMax, xCur % winXMax);
}

void Frupal::lkrt()
{
  xCur -= -1;
  if(xCur >= ((multx+1)*winXMax) ||xCur >= xMax)
    xCur = (multx * winXMax);
  curs_set(1); //Display cursor when it moves
	wmove(curWin, yCur % winYMax, xCur % winXMax);
}

//moves character by offsets passed in
char Frupal::heroMove(int yOffset, int xOffset){
	if(validMove(yHero + yOffset, xHero + xOffset)){
		mvwdelch(curWin, yHero, xHero);

		yHero += yOffset;
		xHero += xOffset;
		showMap();//update map

		if(!mainGuy.modEner(terrainInfo.get_travel_cost(terrainMap[yHero][xHero]))){
			return loseGame();
		}

    //moving our hero now updates the cursor location to him
    yCur = yHero;
    xCur = xHero;

    //And hides the cursor
    curs_set(0);
	}

	mainGuy.showHeroInfo();
  return ' ';
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

	}else if(itemMap[y][x]){
		food * foodptr = dynamic_cast<food*>(itemMap[y][x]);
		if(foodptr){
			if(mainGuy.purchaseItem(foodptr) == true){
				delete itemMap[y][x];
				itemMap[y][x] = NULL;
			}
			foodptr = NULL;
			return true;
		}
	
		tool * toolptr = dynamic_cast<tool*>(itemMap[y][x]);
		if(toolptr){
			if(mainGuy.purchaseItem(toolptr) == true){
				delete itemMap[y][x];
				itemMap[y][x] = NULL;
			}

			toolptr = NULL;
			return true;
		}

		binocular * binocptr = dynamic_cast<binocular*>(itemMap[y][x]);
		if(binocptr){
			if(mainGuy.purchaseItem(binocptr) == true){
				delete itemMap[y][x];
				itemMap[y][x] = NULL;
			}

			binocptr = NULL;
			return true;
		}

		clue * clueptr = dynamic_cast<clue*>(itemMap[y][x]);
		if(clueptr){
			clueptr->discover();
			clueptr->display_info();
			return true;
		}
		
		treasure_chest * treasureptr = dynamic_cast<treasure_chest*>(itemMap[y][x]);
		if(treasureptr){
			treasureptr->discover();
			treasureptr->display_info();
			if(mainGuy.modWhif(treasureptr->get_amount()))
			{
				delete itemMap[y][x];
				itemMap[y][x] = NULL;
			}
			refresh();
			return true;
		}

		//TODO this function is getting out of hand
		//Make this into it's own function, function is almost 100 lines
		obstacle * obstacleptr = dynamic_cast<obstacle*>(itemMap[y][x]);
		if(obstacleptr){
			breakObstacle(obstacleptr, y, x);
			return true;
		}
	}

	return true;
}
		
void Frupal::breakObstacle(obstacle * item, int y , int x){	//breaks obstacle at coordinates
	tool * copy = NULL;
	if(!mainGuy.selectTool(copy, item->get_kind_int())){	//no tool selected
		if(!mainGuy.modEner(item->get_b_energy())) loseGame();
		else{
			 delete itemMap[y][x];
			 itemMap[y][x] = NULL;
		}
	}
	else{						//tool selected
		if(!mainGuy.modEner(item->get_b_energy() / copy->get_divisor())){
			loseGame();
		}else{
			 delete itemMap[y][x];
			 itemMap[y][x] = NULL;
		}
	}
	if(copy != NULL){	//deallocate the copy
		delete copy;
		copy = NULL;	
	}	
	item = NULL;

}

//function displays loss and waits to exit game //TODO
char Frupal::loseGame(){
  
  char ch = ' ';
  int pretty = 1;
  nodelay(curWin,  true);
  while(ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N' && ch != 'q' && ch != 'Q')
  {
    if(pretty >= 8)
      pretty = 1;

    werase(curWin);
    wattron(curWin, COLOR_PAIR(pretty));
    mvwaddstr(curWin, winYMax/2, (winXMax/2)-5, "GAME OVER!");
    wattroff(curWin, COLOR_PAIR(pretty));
    wattron(curWin, COLOR_PAIR(8-pretty));
    mvwaddstr(curWin, winYMax/2+1, (winXMax/2)-8, "Play Again (Y/N)");
    wattroff(curWin, COLOR_PAIR(8-pretty));
    ch = wgetch(curWin);
    ++pretty;
    usleep(175000);
  }
  nodelay(curWin, false);
  if(ch == 'n' || ch == 'N' || ch == 'q' || ch == 'Q')
  {
    return 'q';
  }
  return 'r';
}

//function displays win and waits to exit game //TODO
char Frupal::winGame(){
  char ch = ' ';
  int pretty = 0;
  nodelay(curWin,  true);
  while(ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N' && ch != 'q' && ch != 'Q')
  {
    if(pretty >= 2)
      pretty = 0;

    werase(curWin);
    wattron(curWin, COLOR_PAIR(7+pretty));
    mvwaddstr(curWin, winYMax/2, (winXMax/2)-8, "A WINNER IS YOU!");
    wattroff(curWin, COLOR_PAIR(7+pretty));
    wattron(curWin, COLOR_PAIR(8-pretty));
    mvwaddstr(curWin, winYMax/2+1, (winXMax/2)-8, "Play Again (Y/N)");
    wattroff(curWin, COLOR_PAIR(8-pretty));
    ch = wgetch(curWin);
    ++pretty;
    usleep(175000);
  }
  nodelay(curWin, false);
  if(ch == 'n' || ch == 'N' || ch  == 'q' || ch == 'Q')
  {
    return 'q';
  }
  return 'r';
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
			showCurInfo();
      break;
    case KEY_DOWN://cursor down
			lkdn();
			showCurInfo();
      break;
    case KEY_LEFT://cursor left
			lklt();
			showCurInfo();
      break;
    case KEY_RIGHT://cursor right
			lkrt();
			showCurInfo();
      break;
		case 'w'://hero up
			ch = heroMove(-1, 0);
			break;
		case 'a'://hero left
			ch = heroMove(0, -1);
			break;
		case 's': //hero down
			ch = heroMove(1, 0);
			break;
		case 'd'://hero right
			ch = heroMove(0, 1);
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
  int range = mainGuy.visionRange();
  for(int y = yHero - range; y <= yHero + range; y++){
    for(int x = xHero - range; x <= xHero + range; x++){
      if(y >= 0 && y < 128 && x >= 0 && x < 128)
			  visitMap[y][x] = true;
		}
	}
}

void Frupal::updateCur()
{
  if(yHero >= winYMax*(multy+1))
  {
    ++multy;
  }else if(yHero < winYMax*(multy) && (multy-1) >= 0) {
    --multy;
  }else if(xHero >= winXMax*(multx+1)) {
    ++multx;
  } else if(xHero < winXMax*(multx) && (multx-1) >= 0) {
    --multx;
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

  werase(curWin);

  updateCur();

  int smolY = winYMax*multy;
  int smolX = winXMax*multx;
  int bigY, bigX;
  
  if(winYMax * (multy+1) > yMax)
    bigY = yMax;
  else
    bigY = winYMax*(multy+1);
  
  if(winXMax * (multx+1) > xMax)
    bigX = xMax;
  else
    bigX = winXMax*(multx+1);

	//updates map
	for(int y = smolY; y < bigY; y++){
		for(int x = smolX; x < bigX; x++){
			
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
				mvwaddch(curWin, y-(winYMax*(multy)), x-(winXMax*(multx)), grovnikIcon);//write space to map
				wattroff(curWin, color);//turn off color pair

			//undiscovered areas
			}else{ 
				wattron(curWin, COLOR_PAIR(6));//turn on color BLACK
				mvwaddch(curWin, y-(winYMax*(multy)),x-(winXMax*(multx)), ' ');//write space to map
				wattroff(curWin, COLOR_PAIR(6));//turn off color BLACK
			}
		}
	}

	//shows hero on screen
	wattron(curWin, COLOR_PAIR(1));//turn on color RED
	mvwaddch(curWin, yHero-(winYMax*(multy)),xHero-(winXMax*(multx)),'@');//write @ to map for hero
	wattroff(curWin, COLOR_PAIR(1));//turn off color RED
}

//shows information on current cursor coordinate
void Frupal::showCurInfo(){
	grovnik * currentGrovnik = itemMap[yCur][xCur];

	//displays cursor info if on discovered tile
	if(visitMap[yCur][xCur]){
		if(currentGrovnik){
			currentGrovnik->display_info(); //if theres a grovnik, display info
		}else{
			//otherwise it displays terrain info
			terrainInfo.display_info(terrainMap[yCur][xCur]);
		}

	}else{ //display if tile not discovered
		terrainInfo.display_info('0');
		mvprintw(4, COLS*.75 + 4, "Darkness rules here");
		refresh();
	}
}
