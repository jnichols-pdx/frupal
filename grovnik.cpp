#include "grovnik.h"

grovnik::grovnik()
{}

void grovnik::display()
{}

void grovnik::display_info()
{}
    
int grovnik::travel_cost()
{return 1;}

//----------------------------------------------------------------------------

meadow::meadow(bool with_tree, bool with_bldr, int y_pstn, int x_pstn)
{
  has_tree = with_tree;
  has_boulder = with_bldr;
  y = y_pstn;
  x = x_pstn;
}
    
void meadow::display()
{
}

void meadow::display_info()
{
}

int meadow::travel_cost()
{return 1;}

//----------------------------------------------------------------------------

swamp::swamp(bool with_tree, bool with_bldr, int y_pstn, int x_pstn)
{
  has_tree = with_tree;
  has_boulder = with_bldr;
  y = y_pstn;
  x = x_pstn;
}

void swamp::display()
{
}

void swamp::display_info()
{
}

int swamp::travel_cost()
{return 2;}

//----------------------------------------------------------------------------

water::water()
{
}

void water::display()
{
}

void water::display_info()
{
}

int water::travel_cost()
{return 0;}   		//boat costs no energy to cross

//----------------------------------------------------------------------------

wall::wall()
{
}

void wall::display()
{
}

void wall::display_info()
{
}

int wall::travel_cost()
{return 100000;}	//cant get through

//----------------------------------------------------------------------------

diamond::diamond()
{
}

void diamond::display()
{
}

void diamond::display_info()
{
}

int diamond::travel_cost()
{return 0;}


