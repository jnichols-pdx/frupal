CPPFLAGS = -g -Wall -Werror

frupal: grovnik.o terrain.o frupal.o hero.o main.o
	g++ $(CPPFLAGS) grovnik.o main.o frupal.o terrain.o hero.o -o frupal -lncurses

grovnik.o: grovnik.h grovnik.cpp
	g++ -g -c grovnik.cpp
  
main.o: main.cpp
	g++ -g -c main.cpp
  
hero.o: hero.h hero.cpp
	g++ -g -c hero.cpp
  
frupal.o: frupal.h frupal.cpp
	g++ -g -c frupal.cpp
  
terrain.o: terrain.h terrain.cpp
	g++ -g -c terrain.cpp

clean:
	rm *.o frupal

run:
	make && ./frupal
