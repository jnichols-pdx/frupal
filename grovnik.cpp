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

binocular::binocular()
{
	
}

binocular::~binocular()
{
	
}

void binocular::display_info()
{
	
}

treasure_chest::treasure_chest()
{

}

treasure_chest::~treasure_chest()
{

}

void treasure_chest::display_info()
{
	
}

royal_diamond::royal_diamond()
{
	
}

royal_diamond::~royal_diamond()
{
	
}

void royal_diamond::display_info()
{
	
}

obstacle::obstacle()
{

}

obstacle::~obstacle()
{

}

void obstacle::display_info()
{
	
}

tool::tool()
{
	
}

tool::~tool()
{
	
}

void tool::display_info()
{
	
}

food::food()
{
	
}

food::~food()
{
	
}

void food::display_info()
{
	
}

clue::clue()
{
	
}

clue::~clue()
{
	
}

void clue::display_info()
{
	
}
