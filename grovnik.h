//This file is for managing the classes of the grovniks

#include "frupal.h"


//base class for grovniks
class grovnik
{
	public:
		grovnik();
		grovnik(char character);
		char get_character() const;
		
		//virtual functions
		virtual ~grovnik();
		virtual void display_info() = 0;   //displays information of the grovnik
		
	protected:
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
		treasure_chest(int amount);
		~treasure_chest();
		void display_info();
	protected:
	
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
		void display_info();
	protected:
	
	private:	
};

class tool : public grovnik
{
	public:
		tool();
		tool(int type);
		~tool();
		void display_info();
	protected:
		char * name;
	
	private:	
};

class food : public grovnik
{
	public:
		food();
		food(int type);
		~food();
		void display_info();
	protected:
	
	private:	
};

class clue : public grovnik
{
	public:
		void display_info();
	protected:
	
	private:	
};
