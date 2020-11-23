//This file is for managing the classes of the grovniks

#ifndef GROVNIK_H
#define GROVNIK_H
#include <ncurses.h>


#include <cmath> //do we need this? TODO
#include <stdio.h>

//i think we only need to stick to one of these
//or remove both and stick to char arrays TODO
#include <string> 
#include <cstring>
#include <sstream>

//what is this for? TODO
#include <unistd.h>

//base class for grovniks
class grovnik
{
	public:
		grovnik();
		grovnik(char character);
		char get_character() const;
		char * itos(int, char*); //converts int to string for displays
		
		//virtual functions
		virtual ~grovnik();
		virtual void display_info() = 0;   //displays information of the grovnik
    friend std::istream& operator>> (std::istream& source, grovnik& destination);
		
	protected:
    virtual void read(std::istream & source);
		char character;

	private:
};

class binocular : public grovnik
{
	public:
		binocular();
		~binocular();
		void display_info();
	protected:
	
	private:
};

class treasure_chest : public grovnik
{
	public:
		treasure_chest();
		treasure_chest(char * name, int amount);
		~treasure_chest();
		int get_amount();
    char * get_name();
		void display_info();
	protected:
    char * name;
		int amount;
    virtual void read(std::istream & source);
	
	private:	
};

class royal_diamond : public grovnik
{
	public:
		royal_diamond();
		~royal_diamond();
		void display_info();
	protected:
	
	private:	
};

class obstacle : public grovnik
{
	public:
		obstacle();
		obstacle(char * name, char * name_b, int b_energy);
    ~obstacle();
		void display_info();
		char * get_name();
		char * get_name_b();
		int get_b_energy();
		
	protected:
		char * name; //name of obstacle
		char * name_b; //name of tool that can break it
		int b_energy; //amount of energy that is required to break it
    virtual void read(std::istream & source);
	
	private:	
};

class tool : public grovnik
{
	public:
		tool();
		tool(char * name, char * description, int cost, int divisor);
		tool(tool & to_copy);	//copy constructor
		~tool();
		void display_info();			//displays tool description in the menu
		void display_name(int y);	//displays tool name in the menu at specific y coordinate
		char * get_name();
		int get_cost();
		bool check_equal(const char * item);
	protected:
		char * name;
    char * description;
		int cost;
    int divisor;
    virtual void read(std::istream & source);
	
	private:	
};

class food : public grovnik
{
	public:
		food();
		food(char * name, int cost, int energy);
		~food();
		void display_info();
		char * get_name();
		int get_cost();
		int get_energy();
	protected:
		char * name; //food name
		int cost; //food cost
		int energy; //food energy
    virtual void read(std::istream & source);
	
	private:	
};

class clue : public grovnik
{
	public:
		clue();
		~clue();
		clue(char * clue);
		char * get_clue();
		void display_info();
	protected:
		char * clueText; //clue string
    virtual void read(std::istream & source);
	
	private:	
};

#endif
