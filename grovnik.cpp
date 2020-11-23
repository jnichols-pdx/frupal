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

char * grovnik::itos(int num, char * numStr){
	sprintf(numStr, "%d", num);
	return numStr;
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

binocular::binocular() : grovnik('B')
{
	
}

binocular::~binocular()
{
	
}

void binocular::display_info()
{
	
}

//-------------------------------------------------------------------
//TODO

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
obstacle::obstacle() : grovnik('!'), name(NULL), name_b(NULL), b_energy(0)
{

}

//constructor with args
obstacle::obstacle(char * name, char * name_b, int b_energy) : grovnik('!')
{
	this->name = new char[strlen(name)+1];
	strcpy(this->name,name);
	
	this->name_b = new char[strlen(name_b)+1];
	strcpy(this->name_b,name_b);
	
	this->b_energy = b_energy;
}

//destructor
obstacle::~obstacle()
{
	if(name){
		delete [] name;
		name = NULL;
	}

	if(name_b){
		delete [] name_b;
		name_b = NULL;
	}
}

void obstacle::display_info()
{
	
}

char * obstacle::get_name()
{
	return name;
}

char * obstacle::get_name_b()
{
	return name_b;
}

int obstacle::get_b_energy()
{
	return b_energy;
}

//virtual helper to allow istream >> obstacleObject
void obstacle::read(istream & source)
{
  string temp;
  source >> temp;
  name_b = new char[temp.length() + 1];
  strcpy(name_b,temp.c_str());
  source >> b_energy;
  getline(source, temp);
  name = new char[temp.length() + 1];
  strcpy(name,temp.c_str());
}

//-------------------------------------------------------------------

tool::tool() : grovnik('T'), name(NULL), description(NULL), cost(0), divisor(1)
{}

//constructor with args
tool::tool(char * name, char * description, int cost, int divisor) : grovnik('T')
{
	this->name = new char[strlen(name)+1];
	strcpy(this->name,name);
	
	this->description = new char[strlen(description)+1];
	strcpy(this->description,description);

	this->cost = cost;

  this->divisor = divisor;
}

tool::~tool(){
	if(name != NULL){
		delete [] name;	
		name = NULL;
	}

	if(description != NULL){
		 delete [] description;	
		name = NULL;
	}
}
		
tool::tool(tool & to_copy){
	name = new char[strlen(to_copy.name)+1];
	strcpy(name,to_copy.name);
	description = new char[strlen(to_copy.description)+1];
	strcpy(description,to_copy.description);
	cost = to_copy.cost;
	divisor = to_copy.divisor;
}

void tool::display_info()
{
	char costStr[5] = {0};
	char divisorStr[3] = {0};
	int y, x, yMax, xMax = 0;
	getmaxyx(stdscr, yMax, xMax);
	xMax = xMax * .75 + 3;

	mvprintw(4, xMax, "Cursor Grovnick Info: ");

	mvprintw(5, xMax, "Tool: ");	
	getyx(stdscr, y, x);
	mvprintw(5, x, name);

	mvprintw(6, xMax, "Description: ");
	getyx(stdscr, y, x);
	mvprintw(6, x, name);

	mvprintw(7, xMax, "Cost: ");
	getyx(stdscr, y, x);
	mvprintw(7, x, itos(cost, costStr));

	mvprintw(8, xMax, "Energy Divisor: ");
	getyx(stdscr, y, x);
	mvprintw(8, x, itos(divisor, divisorStr));	

	refresh();
	
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

//virtual helper to allow istream >>toolObject 
void tool::read(istream & source)
{
  string temp;
  source >> temp;
  name = new char[temp.length() + 1];
  strcpy(name,temp.c_str());
  source >> divisor >> cost;
  getline(source, temp);
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
	int y, x, yMax, xMax = 0;
	getmaxyx(stdscr, yMax, xMax);
	xMax = xMax * .75 + 3;


	mvprintw(4, xMax, "Cursor Grovnick Info: ");

	mvprintw(5, xMax, "Food: ");
	getyx(stdscr, y, x);
	mvprintw(y, x, name);

	mvprintw(6, xMax, "Cost: ");
	getyx(stdscr, y, x);
	mvprintw(6, x, itos(cost, costStr));

	mvprintw(7, xMax, "Energy: +");
	getyx(stdscr, y, x);
	mvprintw(7, x, itos(energy, energyStr));	

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
	if(clueText){
		delete [] clueText;
		clueText = NULL;
	}
}

void clue::display_info()
{	
	int y, x = 0;
	getmaxyx(stdscr, y, x);
	x = x * .75 + 3;

	mvprintw(4, x, "Cursor Grovnick Info: ");
	mvprintw(5, x, clueText);

	refresh();
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
