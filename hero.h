#include "grovnik.h"
#include "menu.h"

const int INVSIZE = 10;

class Hero {
public:
  Hero();                                 // Hero constructor
  Hero(int whif, int nRG, int range = 1); // Hero constructor
  ~Hero();
  bool modEner(int nRG); // modify energy - adds by default. To lower energy,
                         // send in negative number
  bool modWhif(int whif); // modify whiffles - adds by default. To lower number
                          // of whiffles, send in negative number
  void showHeroInfo();
  int visionRange(); // Returns how far the hero can see.

  bool checkInventory(
      const char *item); // check if the hero has this in their inventory,
                         // returns false when its not in it
  bool addTool(tool *item); // returns false if inventory is full, unless a ship
                            // is being added it will add the ship
  bool selectTool(tool *&item, int obstacleType,
                  int menuRow); // selects a tool and copies it into the item
                                // argument, returns false if inventory is empty
                                // or if the hero selects the ship. The hero can
                                // not remove the ship from their inventory
  bool purchaseItem(grovnik *item); // asks the user if they want to buy an
                                    // item, checks if its food or tools

private:
  int select(int obstacleType, int menuRow);

  int whiffles;   // hero whiffles
  int energy;     // hero energy
  int vision;     // how far the hero can see.
  bool waterWalk; // can the hero travel on water tiles
  int items;      // items in the inventory

  tool *inventory[INVSIZE + 1]; // 10 inventory items
};
