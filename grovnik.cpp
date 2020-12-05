//grovnik class functions

#include "grovnik.h"

using namespace::std;
using namespace::menu;

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

//Changes occurrences of the string "\n" inside source to '\n' characters.
void grovnik::convertNewlines(string & source){
  int idx = -2;
  while((idx = (int)source.find("\\n")) >= 0)
  {
     source.replace(idx, 1, "\n");
     source.erase(idx + 1,1);
  }
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

binocular::binocular() : grovnik('B'), cost(0), range(2)
{
	
}

//constructor with args
binocular::binocular(int cost, int range) : grovnik('B')
{
	this->cost = cost;
	this->range = range;
}

binocular::~binocular()
{
	
}

int binocular::display_info()
{
	char costStr[5] = {0};
	char rangeStr[4] = {0};

	int row = 4;
	clearLines(row);


	displayStat(row, "Cursor Grovnik Info: ");
	displayStat(row, "Binoculars: ");

	displayStat(row, "Cost: ");
	--row;
	displayStat(row, itos(cost, costStr), 7);

	displayStat(row, "Sight: +");
	--row;
	displayStat(row, itos(range -1, rangeStr), 9);

	refresh();
	return row;
}

//returns the binoculars cost
int binocular::get_cost()
{
	return cost;
}

//returns the binoculars vision range
int binocular::get_range()
{
	return range;
}

//virtual helper to allow istream  >> binocularObject
void binocular::read(istream & source) {
  //override values from default constructor to allow error checking
  cost = -1;
  range = -1; 

  source >> cost;
  if(cost <= 0 && source.fail())
    throw("Incorrect binoculars: missing or invalid <cost>.");

  if(cost > 9999)
    throw "Maximum allowed whiffle <cost> is 9999.";

  source >> range;
  if(range <= 0 && source.fail())
    throw("Incorrect binoculars: missing or invalid <distance>.");

  if(range > 999)
    throw "Maximum allowed <distance> is 999.";

  string temp;
  getline(source,temp);
  if(temp.find_first_not_of(" \n\r\t") != string::npos)
    throw("Incorrect binoculars: found unexpected text on line after <distance>.");
  
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
int ship::display_info()
{
	char costStr[5] = {0};
	int row = 4;

	clearLines(row);


	displayStat(row, "Cursor Grovnik Info: ");
	displayStat(row, "Sailing Ship: ");

	displayStat(row, "Cost: ");
	--row;
	displayStat(row, itos(cost, costStr), 7);

	displayStat(row, "Allows free travel on water.");

	refresh();
	return row;
}

//returns the ship cost
int ship::get_cost()
{
	return cost;
}

//virtual helper to allow istream  >> shipObject
void ship::read(istream & source)
{
  //override values from default constructor to allow error checking
  cost = -1;

  source >> cost;
  if(cost <= 0 && source.fail())
    throw "Incorrect ship: missing or invalid whiffle <cost>.";
  if(cost > 9999)
    throw "Maximum allowed whiffle <cost> is 9999.";

  string temp;
  getline(source,temp);
  if(temp.find_first_not_of(" \n\r\t") != string::npos)
    throw("Incorrect ship: found unexpected text on line after <cost>.");
}

//-------------------------------------------------------------------


treasure_chest::treasure_chest() : grovnik('$'), name(NULL), amount(0), discovered(false)
{

}

treasure_chest::treasure_chest(char * name, int amount) : grovnik('$'), discovered(false)
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

int treasure_chest::display_info()
{
	int row = 4;
	clearLines(row);

	if(discovered){
	displayStat(row, "Cursor Grovnik Info: ");
	displayStat(row, "Treasure: ");
	--row;
	displayStat(row, name, 11); //offset of 7
	displayStat(row, "Collecting Treasure");
	}else{	
		displayStat(row, "???", 4);
	}
	
	refresh();
	return row;
	
}

char * treasure_chest::get_name()
{
	return name;
}

int treasure_chest::get_amount()
{
	return amount;
}

void treasure_chest::discover(){
	discovered = true;
}

//virtual helper to allow istream  >> treasureChestObject
void treasure_chest::read(istream & source)
{
  //override values from default constructor to allow error checking
  amount = -1;

  source >> amount;
  if(amount <= 0 && source.fail())
    throw "Incorrect treasure: missing or invalid <value>";

  //strip leading whitespace before using getline()
  source >> ws;

  string temp;
  getline(source, temp);

  //Strip any trailing '\r' characters from input.
  if(temp[temp.length() -1] == '\r')
    temp.erase(temp.length() -1);

  convertNewlines(temp);

  if(temp.length() == 0)
    throw "Incomplete treasure: missing <description>.";

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

int royal_diamond::display_info()
{
	int row = 4;
	clearLines(row);

	displayStat(row, "Cursor Grovnik Info: ");
	displayStat(row, "Royal Diamond!");
	displayStat(row, "Grab to win!");
	refresh();
	return row;	
}

//virtual helper to allow istream  >> clueObject
void royal_diamond::read(istream & source)
{
  string temp;
  getline(source, temp);

  if(temp.find_first_not_of(" \n\r\t") != string::npos)
    throw("Incorrect diamonds: found unexpected text after on line after <y location>.");

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
    toolTypes.push_back(toAdd);
    return toolTypes.size()-1;
  }
  else
    return loc;
}

//appends toAdd to the obstacleTypes vector if it isn't already present
//returns the index where toAdd was found or placed in obstacleTypes 
int toolObstacle::add_obstacle_typename(const string toAdd)
{
  int loc = find_string(obstacleTypes,toAdd.c_str());
  if(-1 == loc)
  {
    obstacleTypes.push_back(toAdd);
    return obstacleTypes.size()-1;
  }
  else
    return loc;
}

int toolObstacle::find_string(const vector<string> & vec, const char * toFind)
{
  for(int i = 0; i < (int) vec.size(); ++i)
  {
    if(vec[i].compare(toFind) == 0)
      return i;
  }
  return -1;
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

int obstacle::display_info()
{
	char energyStr[5] = {0};

	int row = 4;
	clearLines(row);

	displayStat(row, "Grovnik Info: ");
  displayStat(row, "Obstacle Kind: ");
  --row;
	displayStat(row, get_kind_text(), 16);

	displayStat(row, "Description: ");
	displayStat(row, description, 4); //offset of 7

	displayStat(row, "Energy: ");
	displayStat(row, itos(b_energy, energyStr), 4);	

	refresh();
	return row;	
}

const char * obstacle::get_description()
{
	return description;
}

int obstacle::get_b_energy()
{
	return (-b_energy);
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
  //override values from default constructor to allow error checking
  b_energy = -1;

  string temp;
  source >> temp; //Holds obstacle kind
  if(temp.length() == 0)
    throw "Incomplete obstacle: missing <kind>, <energy cost> and <description>.";

  kind = add_obstacle_typename(temp.c_str());
  source >> b_energy;
  if(b_energy <= 0 && source.fail())
    throw "Incorrect obstacle: missing or invalid <energy <cost>.";

  if(b_energy > 9999)
    throw "Maximum allowed <energy cost> is 9999.";

  //strip leading whitespace before using getline()
  source >> ws;

  temp.erase();
  getline(source, temp); //Holds the obstacle's description

  //Strip any trailing '\r' characters from input.
  if(temp[temp.length() -1] == '\r')
    temp.erase(temp.length() -1);

  convertNewlines(temp);

  if(temp.length() == 0)
    throw "Incomplete obstacle: missing <description>.";

  description= new char[temp.length() + 1];
  strcpy(description,temp.c_str());
}

//-------------------------------------------------------------------

tool::tool() : toolObstacle('T'), description(NULL), target_count(0), kind(0), cost(0), divisor(1)
{}

//constructor with args
tool::tool(char * description, int kind, int cost, int divisor) : toolObstacle('T')
{
	this->description = new char[strlen(description)+1];
	strcpy(this->description,description);

  this->kind = kind;

	this->cost = cost;

  this->divisor = divisor;
  target_count = 0; //TODO - functions to add targets after initialization? or pass a list object?
}

tool::~tool(){
	if(description != NULL){
		delete [] description;	
		description = NULL;
	}
  delete [] targets;

}
		
tool::tool(tool & to_copy){
	description = new char[strlen(to_copy.description)+1];
	strcpy(description,to_copy.description);
  target_count = to_copy.target_count;
  targets = new int[target_count];
  for(int i = 0; i < target_count; ++i)
    targets[i] = to_copy.targets[i];

  kind= to_copy.kind;
	cost = to_copy.cost;
	divisor = to_copy.divisor;
}

int tool::display_info()
{
	char costStr[5] = {0};
	char divisorStr[5] = {0};

	int row = 4;
	clearLines(row);

	displayStat(row, "Cursor Grovnik Info: ");
	displayStat(row, "Tool Kind: ");
	--row;
	displayStat(row, get_kind_text(), 12);

	displayStat(row, "Description: ");
	displayStat(row, description, 4);

  displayStat(row, "Breaks: ");
  for(int i = 0; i < target_count; ++i)
    displayStat(row, obstacleTypes[targets[i]].c_str(),4);


	displayStat(row, "Cost: ");
	--row;
	displayStat(row, itos(cost, costStr), 7);

	displayStat(row, "Energy Divisor: ");
	--row;
	displayStat(row, itos(divisor, divisorStr), 16);	

	refresh();
	return row;
}

void tool::display_name(int y){	//displays tool name in the menu 
	if(description == NULL) return;
	displayStat(y, description);
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
		
int tool::get_divisor() 		//returns divisor
{
	return divisor;
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
  //override values from default constructor to allow error checking
  target_count = -1;
  divisor = -1;
  cost = -1;

  string temp;
  source >> temp; //holds tool kind
  if(temp.length() == 0)
    throw "Incomplete tool: missing <kind>, <target_count>, <targets...>, <divisor>, <cost> and <description>.";

  kind = add_tool_typename(temp);

  source >> target_count; 
  if(target_count <= 0 && source.fail())
    throw "Incorrect tool: missing or invalid <target_count>.";

  temp.erase();
  targets = new int[target_count];
  for(int i = 0; i < target_count; ++i)
  {
    source >> temp;
    if(temp.length() == 0)
      throw "Incomplete tool: missing (or too few) <targets...>, <divisor>, <cost> and <description>.";
    targets[i] = add_obstacle_typename(temp);
    temp.erase();
  }

  source >> divisor;
  if(divisor <= 0 && source.fail())
    throw "Incorrect tool: missing or invalid <divisor>.";
  if(divisor > 9999)
    throw "Maximum allowed <divisor> is 9999.";

  source >> cost;
  if(cost <= 0 && source.fail())
    throw "Incorrect tool: missing or invalid <cost>.";
  if(cost > 9999)
    throw "Maximum allowed whiffle <cost> is 9999.";

  //strip leading whitespace before using getline()
  source >> ws;

  getline(source, temp); //holds tool description

  //Strip any trailing '\r' characters from input.
  if(temp[temp.length() -1] == '\r')
    temp.erase(temp.length() -1);

  convertNewlines(temp);

  if(temp.length() == 0)
    throw "Incomplete tool: missing <description>.";

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

int food::display_info()
{
	char costStr[5] = {0};
	char energyStr[5] = {0};

	int row = 4;
	clearLines(row);


	displayStat(row, "Cursor Grovnik Info: ");
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
	return row;
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
  //override values from default constructor to allow error checking
  cost = -1;
  energy = -1;

  source >> cost;
  if(cost<= 0 && source.fail())
    throw "Incorrect food: missing or invalid energy <cost>.";
  if(cost > 9999)
    throw "Maximum allowed whiffle <cost> is 9999.";

  source >> energy;
  if(energy <= 0 && source.fail())
    throw "Incorrect food: missing or invalid energy <energy>.";
  if(energy > 9999)
    throw "Maximum allowed <energy> is 9999.";

  //strip leading whitespace before using getline()
  source >> ws;

  string temp;
  getline(source, temp);

  //Strip any trailing '\r' characters from input.
  if(temp[temp.length() -1] == '\r')
    temp.erase(temp.length() -1);

  convertNewlines(temp);

  if(temp.length() == 0)
    throw "Incomplete food: missing <description>.";

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

int clue::display_info()
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
	return row;
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
 
  convertNewlines(temp);

  if(temp.length() == 0)
    throw "Incomplete clue: missing <description>.";

  clueText = new char[temp.length() + 1];
  strcpy(clueText,temp.c_str());
}
