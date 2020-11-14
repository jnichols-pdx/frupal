//this file is for managing the classes of the grovniks

#include "frupal.h"


class grovnik   	//base class for grovniks
{
  public:
    grovnik();
    virtual void display();	//displays correct color and spot
    virtual void display_info();   //displays information of the grovik in the menu
    virtual int travel_cost();	//returns cost to travel

  protected:
    bool has_tree;	//true if there is a tree in the grovnik
    bool has_boulder;   //true if there is a boulder in the grovnik
    int cost_travel;    //cost of energy for player to travel through 
    int y;		//y position on the map
    int x;		//x position on the map
};

class meadow: public grovnik
{
  public:
    meadow(bool with_tree, bool with_bldr, int y_pstn, int x_pstn);
    void display();
    void display_info();
    int travel_cost();

};

class swamp: public grovnik
{
  public:
    swamp(bool with_tree, bool with_bldr, int y_pstn, int x_pstn);
    void display();
    void display_info();
    int travel_cost();
};

class water: public grovnik
{
  public:
    water();
    void display();
    void display_info();
    int travel_cost();
};

class wall: public grovnik
{
  public:
    wall();
    void display();
    void display_info();
    int travel_cost();
};

class diamond: public grovnik
{
  public:
    diamond();
    void display();
    void display_info();
    int travel_cost();
};


