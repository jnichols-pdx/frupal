//grovnik class functions


#include "grovnik.h"

//grovnik default constructor
grovnik::grovnik() : character(NULL)
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

//-------------------------------------------------------------------

binocular::binocular()
{
	
}

binocular::~binocular()
{
	
}

void binocular::display_info()
{
	
}

//-------------------------------------------------------------------

treasure_chest::treasure_chest()
{

}

treasure_chest::~treasure_chest()
{

}

void treasure_chest::display_info()
{
	
}

//-------------------------------------------------------------------

royal_diamond::royal_diamond()
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
obstacle::obstacle() : name(NULL), name_b(NULL), b_energy(0)
{

}

//constructor with args
obstacle::obstacle(char * name, char * name_b, int b_energy)
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
	delete [] name;
	delete [] name_b;
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

//-------------------------------------------------------------------

tool::tool() : name(NULL)
{
	
}

//constructor with args
tool::tool(char * name)
{
	this->name = new char[strlen(name)+1];
	strcpy(this->name,name);
}

tool::~tool()
{
	delete [] name;
}

void tool::display_info()
{
	
}

char * tool::get_name()
{
	return name;
}

//-------------------------------------------------------------------

//default constructor
food::food() : name(NULL), cost(0), energy(0)
{
	
}

//constructor with args
food::food(char * name, int cost, int energy)
{
	this->name = new char[strlen(name)+1];
	strcpy(this->name,name);

	this->cost = cost;

	this->energy = energy;
}

food::~food()
{
	delete [] name;
}

void food::display_info()
{
	
}

char * food::name()
{
	return name;
}

int food::cost()
{
	return cost;
}

int food::energy()
{
	return energy;
}

//-------------------------------------------------------------------

clue::clue()
{
	
}

clue::~clue()
{
	
}

void clue::display_info()
{
	
}
