//The item class will take in a player as an argument
//and perform actions on the player depending on which
//item the player uses

#include "frupal.h"


class item
{
	public:
		item();
		~item();
		void binocular(Hero * to_edit);
		void treasure_chest(Hero * to_edit);
		void royal_diamond(Hero * to_edit);
		
	protected:
	
	private:
};
