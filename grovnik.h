// This file is for managing the classes of the grovniks

#ifndef GROVNIK_H
#define GROVNIK_H
#include <ncurses.h>

#include <cstring>
#include <stdio.h>

// Used for reading from files.
#include <istream>
#include <string>

#include <vector>

#include "menu.h"

// base class for grovniks
class grovnik {
public:
  grovnik();
  grovnik(char character);
  char get_character() const;
  char *itos(int, char *); // converts int to string for displays
  void convertNewlines(std::string &source);

  // virtual functions
  virtual ~grovnik();
  virtual int display_info() = 0; // displays information of the grovnik
  friend std::istream &operator>>(std::istream &source, grovnik &destination);

protected:
  virtual void read(std::istream &source);
  char character;

private:
};

class binocular : public grovnik {
public:
  binocular();
  binocular(int cost, int range);
  ~binocular();
  int display_info();
  int get_cost();
  int get_range();

protected:
  virtual void read(std::istream &source);
  int cost;
  int range; // how far a hero with these binoculars may see.

private:
};

class ship : public grovnik {
public:
  ship();
  ship(int cost);
  ~ship();
  int display_info();
  int get_cost();

protected:
  virtual void read(std::istream &source);
  int cost;

private:
};

class treasure_chest : public grovnik {
public:
  treasure_chest();
  treasure_chest(char *name, int amount);
  ~treasure_chest();
  int get_amount();
  char *get_name();
  int display_info();
  void discover();

protected:
  char *name;
  int amount;
  virtual void read(std::istream &source);
  bool discovered;

private:
};

class royal_diamond : public grovnik {
public:
  royal_diamond();
  ~royal_diamond();
  int display_info();

protected:
  virtual void read(std::istream &source);

private:
};

class toolObstacle : public grovnik {
public:
  toolObstacle();
  toolObstacle(char disp);

protected:
  static std::vector<std::string> toolTypes;
  static std::vector<std::string> obstacleTypes;
  int find_tool_by_typename(const char *toFind);
  int find_obstacle_by_typename(const char *toFind);
  int add_tool_typename(const std::string toAdd);
  int add_obstacle_typename(const std::string toAdd);
  int find_string(const std::vector<std::string> &vec, const char *toFind);
};

class obstacle : public toolObstacle {
public:
  obstacle();
  obstacle(char *name, int obstacle_type, int b_energy);
  ~obstacle();
  int display_info();
  const char *get_description();
  const char *get_kind_text();
  int get_b_energy();
  int get_kind_int();

protected:
  char *description; // name of obstacle
  int kind;          // Numeric ID for what kind of obstacle this is
  int b_energy;      // amount of energy that is required to break it
  virtual void read(std::istream &source);

private:
};

class tool : public toolObstacle {
public:
  tool();
  tool(char *name, int kind, int cost, int divisor);
  tool(tool &to_copy); // copy constructor
  ~tool();
  int display_info(); // displays tool description in the menu

  // displays tool name in the menu at specific y coordinate
  void display_name(int y);
  const char *get_description();
  const char *get_kind_text();
  int get_cost();
  bool check_if_targets(const int possible_target);
  int get_divisor(); // returns divisor
  bool check_equal(const char *item);

protected:
  char *description;
  int *targets; // Numeric IDs for what kind of obstacle this tool helps remove,
  int target_count; // Length of targets array
  int kind;         // Numeric index into
  int cost;         // Purchase price in whiffles
  int divisor; // integer to divide an obstacles cost by when using this tool
  virtual void read(std::istream &source);

private:
};

class food : public grovnik {
public:
  food();
  food(char *name, int cost, int energy);
  ~food();
  int display_info();
  char *get_name();
  int get_cost();
  int get_energy();

protected:
  char *name; // food name
  int cost;   // food cost
  int energy; // food energy
  virtual void read(std::istream &source);

private:
};

class clue : public grovnik {
public:
  clue();
  ~clue();
  clue(char *clue);
  char *get_clue();
  int display_info();
  void discover();

protected:
  bool discovered; // whether the hero has landed on this clue
  char *clueText;  // clue string
  virtual void read(std::istream &source);
};

#endif
