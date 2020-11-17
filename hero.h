class Hero
{
  public:
	Hero(); //Hero constructor
  	Hero(int whif, int nRG); //Hero constructor
  	void modEner(int nRG); //modify energy - adds by default. To lower energy, send in negative number
  	void modWhif(int Whif); //modify whiffles - adds by default. To lower number of whiffles, send in negative number
  private:
  	int whiffles; //hero whiffles
  	int energy; //hero energy
};
