//grovnik class functions

#include "grovnik.h"

using namespace::std;

//grovnik default constructor
grovnik::grovnik() : character('\0')
{
	
}

//grovnik constructor with arguments
grovnik::grovnik(char character)
{
	this->character = character;
}

//grovnik destructor
//this destructor is virtual
grovnik::~grovnik()
{

}

//grovnik character getter function
char grovnik::get_character() const
{
	return character;
}

//converts int to string and returns the char * passed in
char * grovnik::itos(int num, char * numStr){
	sprintf(numStr, "%d", num);
	return numStr;
}

void grovnik::displayStat(int & row, const char * text, int offset){
	if(!text){return;}
	
	int x = getmaxx(stdscr);
  char * data;
	
	//calculates menu dimensions and lines needed for text display
	int menu_width = (x - (x * .75)) - 1;
  int chunkWidth = menu_width - offset;
	int lines = ceil(((float)strlen(text))/ ((float)chunkWidth));
	int lastLine = lines + row;
  data = new char[chunkWidth + 1];
	
	//wraps text around back to menu on next line
	while(row < lastLine){
		int index = (menu_width - offset) * (row - lastLine + lines);
		strncpy(data, text + index, chunkWidth);
		data[chunkWidth + 1] = '\0';
		mvprintw(row, x - menu_width + offset, data);
		++row;
	}
  delete [] data;

}

//clears data on menu from start to end lines
void grovnik::clearLines(int start, int end){
	if(start == end){return;}
	if(start > end){return;}
	
	int x = getmaxx(stdscr);
	
	move(start, x * .75 + 1);

	clrtoeol();
	clearLines(++start, end);	
}

//grovnik read from stream function
//this function is virtual
void grovnik::read(istream & source)
{

}

//Friend function to allow reading grovnik and derived grovnik classes from streams
istream& operator >> (istream& source, grovnik& destination)
{
  destination.read(source);
  return source;
}

//-------------------------------------------------------------------
//TODO

binocular::binocular() : grovnik('B'), cost(0)
{
	
}

//constructor with args
binocular::binocular(int cost) : grovnik('B')
{
	this->cost = cost;
}

binocular::~binocular()
{
	
}

void binocular::display_info()
{//TODO
	
}

//returns the ship cost
int binocular::get_cost()
{
	return cost;
}

//virtual helper to allow istream  >> binocularObject
void binocular::read(istream & source)
{
  source >> cost;
}

//-------------------------------------------------------------------
//TODO

//default constructor
ship::ship() : grovnik('S'), cost(0)
{
	
}

//constructor with args
ship::ship(int cost) : grovnik('S')
{
	this->cost = cost;
}

//destructor
ship::~ship()
{
	
}

//virtual function
void ship::display_info()
{
	
}

//returns the ship cost
int ship::get_cost()
{
	return cost;
}

//virtual helper to allow istream  >> shipObject
void ship::read(istream & source)
{
  source >> cost;
}

//-------------------------------------------------------------------


treasure_chest::treasure_chest() : grovnik('$'), name(NULL), amount(0)
{

}

treasure_chest::treasure_chest(char * name, int amount) : grovnik('$')
{
	this->name = new char[strlen(name)+1];
	strcpy(this->name,name);
	this->amount = amount;
}

treasure_chest::~treasure_chest()
{
	if(name){
  	delete [] name;
	}

}

void treasure_chest::display_info()
{
	int row = 4;
	clearLines(row);

	displayStat(row, "Cursor Grovnik Info: ");
	displayStat(row, "Treasure: ");
	--row;
	displayStat(row, name, 11); //offset of 7

	refresh();
	
}

char * treasure_chest::get_name()
{
	return name;
}

int treasure_chest::get_amount()
{
	return amount;
}

//virtual helper to allow istream  >> treasureChestObject
void treasure_chest::read(istream & source)
{
  source >> amount;

  //strip leading whitespace before using getline()
  source >> ws;

  string temp;
  getline(source, temp);

  //Strip any trailing '\r' characters from input.
  if(temp[temp.length() -1] == '\r')
    temp.erase(temp.length() -1);

  name = new char[temp.length() + 1];
  strcpy(name,temp.c_str());
}

//-------------------------------------------------------------------
//TODO

royal_diamond::royal_diamond() : grovnik('%') //$ is already in use for treasure_chest
{
	
}

royal_diamond::~royal_diamond()
{
	
}

void royal_diamond::display_info()
{
	int row = 4;
	clearLines(row);

	displayStat(row, "Cursor Grovnik Info: ");
	displayStat(row, "Royal Diamond!");
	displayStat(row, "Grab to win!");
	refresh();
	
}

//-------------------------------------------------------------------

vector<string> toolObstacle::toolTypes;
vector<string> toolObstacle::obstacleTypes;

toolObstacle::toolObstacle()
{
}

toolObstacle::toolObstacle(char disp) : grovnik(disp)
{
}


//returns index of the specified index of toFind in toolTypes, or -1 if not found.
int toolObstacle::find_tool_by_typename(const char * toFind)
{
  return find_string(toolTypes,toFind);
}

//returns index of the specified index of toFind in obstacleTypes, or -1 if not found.
int toolObstacle::find_obstacle_by_typename(const char * toFind)
{

  return find_string(obstacleTypes,toFind);
}

//appends toAdd to the toolTypes vector if it isn't already present
//returns the index where toAdd was found or placed in toolTypes
int toolObstacle::add_tool_typename(const string toAdd)
{
  int loc = find_string(toolTypes,toAdd.c_str());
  if(-1 == loc)
  {
    obstacleTypes.push_back(toAdd);//this feels off
    return obstacleTypes.size()-1;
  }
  else
    return 0;
}

//appends toAdd to the obstacleTypes vector if it isn't already present
//returns the index where toAdd was found or placed in obstacleTypes 
int toolObstacle::add_obstacle_typename(const string toAdd)
{
  int loc = find_string(obstacleTypes,toAdd.c_str());
  if(-1 == loc)
  {
    obstacleTypes.push_back(toAdd);//this feels off
    return obstacleTypes.size()-1;
  }
  else
    return 0;
}

int toolObstacle::find_string(const vector<string> & vec, const char * toFind)
{

return 0;
}

//-------------------------------------------------------------------

//default constructor
obstacle::obstacle() : toolObstacle('!'), description(NULL), kind(0), b_energy(0)
{

}

//constructor with args
obstacle::obstacle(char * description, int kind, int b_energy) : toolObstacle('!')
{
	this->description = new char[strlen(description)+1];
	strcpy(this->description,description);
	
	this->kind = kind;

	this->b_energy = b_energy;
}

//destructor
obstacle::~obstacle()
{
	if(description){
		delete [] description;
		description = NULL;
	}
}

void obstacle::display_info()
{
	char energyStr[5] = {0};

	int row = 4;
	clearLines(row);

	displayStat(row, "Grovnik Info: ");
	displayStat(row, "Obstacle: ");
	displayStat(row, name, 4); //offset of 7

	displayStat(row, "Break w/ ");
	displayStat(row, name_b, 4);

	displayStat(row, "Energy: ");
	displayStat(row, itos(b_energy, energyStr), 4);	

	refresh();
	
}

const char * obstacle::get_description()
{
	return description;
}

int obstacle::get_b_energy()
{
	return b_energy;
}

const char * obstacle::get_kind_text()
{
  return obstacleTypes[kind].c_str();
}

int obstacle::get_kind_int()
{
  return kind;
}

//virtual helper to allow istream >> obstacleObject
void obstacle::read(istream & source)
{
  string temp;
  source >> temp; //Holds obstacle kind
  kind = add_obstacle_typename(temp.c_str());
  source >> b_energy;
  getline(source, temp); 

  //strip leading whitespace before using getline()
  source >> ws;

  getline(source, temp); //Holds the obstacle's description

  //Strip any trailing '\r' characters from input.
  if(temp[temp.length() -1] == '\r')
    temp.erase(temp.length() -1);

  description= new char[temp.length() + 1];
  strcpy(description,temp.c_str());
}

//-------------------------------------------------------------------

tool::tool() : toolObstacle('T'), description(NULL), kind(0), cost(0), divisor(1)
{}

//constructor with args
tool::tool(char * description, int kind, int cost, int divisor) : toolObstacle('T')
{
	this->description = new char[strlen(description)+1];
	strcpy(this->description,description);

  this->kind = kind;

	this->cost = cost;

  this->divisor = divisor;
}

tool::~tool(){
	if(description != NULL){
		delete [] description;	
		description = NULL;
	}

}
		
tool::tool(tool & to_copy){
	description = new char[strlen(to_copy.description)+1];
	strcpy(description,to_copy.description);
  kind= to_copy.kind;
	cost = to_copy.cost;
	divisor = to_copy.divisor;
}

void tool::display_info()
{
	char costStr[5] = {0};
	char divisorStr[3] = {0};

	int row = 4;
	clearLines(row);

	displayStat(row, "Cursor Grovnik Info: ");
	displayStat(row, "Tool: ");
	--row;
	displayStat(row, name, 7); //offset of 7

	displayStat(row, "Description: ");
	displayStat(row, description, 4);

	displayStat(row, "Cost: ");
	--row;
	displayStat(row, itos(cost, costStr), 7);

	displayStat(row, "Energy Divisor: ");
	--row;
	displayStat(row, itos(divisor, divisorStr), 16);	

	refresh();
	
}

void tool::display_name(int y){	//displays tool name in the menu 
	if(description == NULL) return;
	mvwprintw(stdscr, y, COLS*0.75+3, "%s", description);
	refresh();
}

bool tool::check_equal(const char * item)
{
	if(item == NULL) return false;
	if(this->description== NULL) return false;	
	if(strcmp(this->description, item) == 0) return true;
	else return false;
}

int tool::get_cost()
{
	return cost;
}

const char * tool::get_description()
{
    return description;
}

bool tool::check_if_targets(const int possible_target)
{
  bool found = false;
  for(int i = 0; !found && i < target_count; ++i)
    found = (possible_target == targets[i]);

  return found;
}

const char * tool::get_kind_text()
{
    return toolTypes[kind].c_str();
}

//virtual helper to allow istream >>toolObject 
void tool::read(istream & source)
{
  string temp;
  source >> temp; //holds tool kind
  kind = add_tool_typename(temp);
  source >> target_count; //TODO REALLY NEED INPUT VALIDATION IN ALL OF THESE read FUNCTIONS
  targets = new int[target_count];
  for(int i = 0; i < target_count; ++i)
  {
    source >> temp;
    targets[i] = add_obstacle_typename(temp);
  }

  source >> divisor >> cost;

  //strip leading whitespace before using getline()
  source >> ws;

  getline(source, temp); //holds tool description

  //Strip any trailing '\r' characters from input.
  if(temp[temp.length() -1] == '\r')
    temp.erase(temp.length() -1);

  description= new char[temp.length() + 1];
  strcpy(description,temp.c_str());
}

//-------------------------------------------------------------------

//default constructor
food::food() : grovnik('F'), name(NULL), cost(0), energy(0){}

//constructor with args
food::food(char * name, int cost, int energy) : grovnik('F')
{
	this->name = new char[strlen(name)+1];
	strcpy(this->name,name);

	this->cost = cost;

	this->energy = energy;
}

food::~food()
{
	if(name){
		delete [] name;
		name = NULL;
	}
}

void food::display_info()
{
	char costStr[5] = {0};
	char energyStr[4] = {0};

	int row = 4;
	clearLines(row);


	displayStat(row, "Cursor Grovnick Info: ");
	displayStat(row, "Food: ");
	--row;
	displayStat(row, name, 7);

	displayStat(row, "Cost: ");
	--row;
	displayStat(row, itos(cost, costStr), 7);

	displayStat(row, "Energy: +");
	--row;
	displayStat(row, itos(energy, energyStr), 9);	

	refresh();
}

char * food::get_name()
{
	return name;
}

int food::get_cost()
{
	return cost;
}

int food::get_energy()
{
	return energy;
}

//virtual helper to allow istream >> foodObject
void food::read(istream & source)
{
  source >> cost >> energy;

  //strip leading whitespace before using getline()
  source >> ws;

  string temp;
  getline(source, temp);

  //Strip any trailing '\r' characters from input.
  if(temp[temp.length() -1] == '\r')
    temp.erase(temp.length() -1);

  name = new char[temp.length() + 1];
  strcpy(name,temp.c_str());
}

//-------------------------------------------------------------------

//default constructor
clue::clue() : grovnik('?'), discovered(false), clueText(NULL){}

//constructor with args
clue::clue(char * clue) : grovnik('?'), discovered(false)
{
	this->clueText = new char[strlen(clue)+1];
	strcpy(this->clueText,clue);
}

//destructor
clue::~clue()
{
	if(clueText){
		delete [] clueText;
		clueText = NULL;
	}
}

void clue::display_info()
{	
	int row = 4;
	clearLines(row);

	displayStat(row, "Clue: ");
	if(discovered){
		displayStat(row, clueText, 4);

    //Prevent mangling the vertical line of # characters when the
    //last displayStat() call prints text all the way to the right
    //edge of the window
    displayStat(row," ");
	}else{	
		displayStat(row, "???", 4);
	}


	refresh();
}

char * clue::get_clue()
{
	return clueText;
}

void clue::discover(){
	discovered = true;
}

//virtual helper to allow istream  >> clueObject
void clue::read(istream & source)
{
  //strip leading whitespace before using getline()
  source >> ws;

  string temp;
  getline(source, temp);

  //Strip any trailing '\r' characters from input.
  if(temp[temp.length() -1] == '\r')
    temp.erase(temp.length() -1);

  clueText = new char[temp.length() + 1];
  strcpy(clueText,temp.c_str());
}
