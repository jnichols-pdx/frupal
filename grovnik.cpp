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

obstacle::obstacle()
{

}

obstacle::~obstacle()
{

}

void obstacle::display_info()
{
	
}

//-------------------------------------------------------------------

tool::tool() : name(NULL)
{
	
}

tool::~tool()
{
	
}

void tool::display_info()
{
	
}

//-------------------------------------------------------------------

//default constructor
food::food() : name(NULL), cost(0), energy(0)
{
	
}

//constructor with args
food::food(char name, int cost, int energy)
{
	this->name = name;
	this->cost = cost;
	this->energy = energy;
}

food::~food()
{
	
}

void food::display_info()
{
	
}

char food::name
{
	return name;
}

int food::cost
{
	return cost;
}

int food::energy
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