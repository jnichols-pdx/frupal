//this file is for managing the classes of the terrains

#include "frupal.h"


class terrain   	//base class for terrains
{
  public:
    terrain();
		virtual ~terrain();
    virtual void display_info() = 0;   //displays information of the terrain in the menu
    int get_travel_cost();	//returns cost to travel
    int get_color();	//returns color of terrain

  protected:
    int travel_cost;    //cost of energy for player to travel through 
		int color; //color of terrain
};

class meadow: public terrain
{
  public:
		meadow();
		~meadow();
    void display_info();
};

class swamp: public terrain
{
  public:
		swamp();
		~swamp();
    void display_info();
};

class water: public terrain
{
  public:
    water();
		~water();
    void display_info();
};

class wall: public terrain
{
  public:
    wall();
		~wall();
    void display_info();
};

