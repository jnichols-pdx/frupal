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


  //Read all elements from the map file
  while(!mapFile.eof())
  {
    mapFile >> elemName;

    if(elemName.length() == 0) //blank lines
      continue;

    if(elemName[0] == '#') //Comments
    {
      mapFile.ignore(1000, '\n');
      continue;
    }

    if(elemName.compare("terrain:") == 0)
    {
      mapFile >> xMax >> yMax;
      mapFile.ignore(1000, '\n');
//Adjusted for static map size
      for(int i = 0; i < yMax; ++i){
        for(int j = 0; j < xMax; ++j){

          terrainMap[i][j] = mapFile.get();
          visitMap[i][j] = false;
        }
        mapFile.ignore(1000, '\n');
      }
      continue;
    }

    if(elemName.compare("start:") == 0)
    {
      mapFile >> xHero >> yHero;
      mapFile.ignore(1000, '\n');
      continue;
    }

    if(elemName.compare("diamonds:") == 0)
    {
      //TODO: implement
      mapFile.ignore(1000, '\n');
      continue;
    }

    if(elemName.compare("treasure:") == 0)
    {
      //TODO: implement
      mapFile.ignore(1000, '\n');
      continue;
    }

    if(elemName.compare("food:") == 0)
    {
      //TODO: implement
      mapFile.ignore(1000, '\n');
      continue;
    }

    if(elemName.compare("clue:") == 0)
    {
      //TODO: implement
      mapFile.ignore(1000, '\n');
      continue;
    }

    if(elemName.compare("ship:") == 0)
    {
      //TODO: implement
      mapFile.ignore(1000, '\n');
      continue;
    }

    if(elemName.compare("binoculars:") == 0)
    {
      //TODO: implement
      mapFile.ignore(1000, '\n');
      continue;
    }

    if(elemName.compare("obstacle:") == 0)
    {
      //TODO: implement
      mapFile.ignore(1000, '\n');
      continue;
    }

    if(elemName.compare("tool:") == 0)
    {
      //TODO: implement
      mapFile.ignore(1000, '\n');
      continue;
    }

    //Fail if we see unexpected input
    return false;
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

//function displays loss and waits to exit game
void Frupal::loseGame(){
}

//function displays win and waits to exit game
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

	//updates map
	for(int y = 0; y < yMax; y++){
		for(int x = 0; x < xMax; x++){
			
			//discovered areas
			if(visitMap[y][x] == true){
				int color = terrainInfo.get_color(terrainMap[y][x]);//gets color
				wattron(curWin, color);//turn on color pair
				mvwaddch(curWin, y, x, ' ');//write space to map
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
