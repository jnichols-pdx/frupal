//The item class will take in a Hero as an argument
//and perform actions on the Hero depending on which
//item the Hero uses

#include "frupal.h"


class item
{
	public:
		item();
		~item();
		void binocular(Hero * &to_edit);
		void treasure_chest(Hero * &to_edit);
		void royal_diamond(Hero * &to_edit);
		
	protected:
	
	private:
};
