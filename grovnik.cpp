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
{
	
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
  delete [] name;

}

void treasure_chest::display_info()
{
	
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
  string temp;
  getline(source, temp);
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
	
}

//-------------------------------------------------------------------

//default constructor
obstacle::obstacle() : grovnik('!'), name(NULL), obstacle_type(0), b_energy(0)
{

}

//constructor with args
obstacle::obstacle(char * name, int obstacle_type, int b_energy) : grovnik('!')
{
	this->name = new char[strlen(name)+1];
	strcpy(this->name,name);
	
	this->obstacle_type = obstacle_type;

	this->b_energy = b_energy;
}

//destructor
obstacle::~obstacle()
{
	delete [] name;
	name = NULL;
}

void obstacle::display_info()
{
	
}

char * obstacle::get_name()
{
	return name;
}

int obstacle::get_type()
{
  return obstacle_type;
}

int obstacle::get_b_energy()
{
	return b_energy;
}

//virtual helper to allow istream >> obstacleObject
void obstacle::read(istream & source)
{
  string temp;
  source >>obstacle_type >> b_energy;
  getline(source, temp);
  name = new char[temp.length() + 1];
  strcpy(name,temp.c_str());
}

//-------------------------------------------------------------------

tool::tool() : grovnik('T'), name(NULL), target_type(0), cost(0), divisor(1)
{}

//constructor with args
tool::tool(char * name, int target_type, int cost, int divisor) : grovnik('T')
{
	this->name = new char[strlen(name)+1];
	strcpy(this->name,name);
	
  this->target_type = target_type;

	this->cost = cost;

  this->divisor = divisor;
}

tool::~tool(){
	if(name != NULL){
		delete [] name;	
		name = NULL;
	}

}
		
tool::tool(tool & to_copy){
	name = new char[strlen(to_copy.name)+1];
	strcpy(name,to_copy.name);
  target_type = to_copy.target_type;
	cost = to_copy.cost;
	divisor = to_copy.divisor;
}

void tool::display_info()
{
	
}

void tool::display_name(int y){	//displays tool name in the menu 
	if(name == NULL) return;
	mvwprintw(stdscr, y, COLS*0.75+3, "%s", name);
	refresh();
}

bool tool::check_equal(const char * item)
{
	if(item == NULL) return false;
	if(this->name == NULL) return false;	
	if(strcmp(this->name, item) == 0) return true;
	else return false;
}

int tool::get_cost()
{
	return cost;
}

int tool::get_target()
{
	return target_type;
}

//virtual helper to allow istream >>toolObject 
void tool::read(istream & source)
{
  string temp;
  source >> target_type >> divisor >> cost;
  getline(source, temp);
  name = new char[temp.length() + 1];
  strcpy(name ,temp.c_str());
}

//-------------------------------------------------------------------

//default constructor
food::food() : grovnik('F'), name(NULL), cost(0), energy(0)
{
	
}

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
	delete [] name;
	name = NULL;
}

void food::display_info()
{
	
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
  string temp;
  getline(source, temp);
  name = new char[temp.length() + 1];
  strcpy(name,temp.c_str());
}

//-------------------------------------------------------------------

//default constructor
clue::clue() : grovnik('?'), clueText(NULL)
{}

//constructor with args
clue::clue(char * clue) : grovnik('?')
{
	this->clueText = new char[strlen(clue)+1];
	strcpy(this->clueText,clue);
}

//destructor
clue::~clue()
{
	delete [] clueText;
	clueText = NULL;
}

void clue::display_info()
{
	
}

char * clue::get_clue()
{
	return clueText;
}

//virtual helper to allow istream  >> clueObject
void clue::read(istream & source)
{
  string temp;
  getline(source, temp);
  clueText = new char[temp.length() + 1];
  strcpy(clueText,temp.c_str());
}
