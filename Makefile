CPPFLAGS = -g -Wall -Werror

frupal: grovnik.o terrain.o frupal.o hero.o main.o
	g++ $(CPPFLAGS) main.o frupal.o hero.o grovnik.o terrain.o -o frupal -lncurses
  
main.o: main.cpp
	g++ $(CPPFLAGS) -c main.cpp
  
hero.o: hero.h hero.cpp
	g++ $(CPPFLAGS) -c hero.cpp
  
frupal.o: frupal.h frupal.cpp
	g++ $(CPPFLAGS) -c frupal.cpp
  
grovnik.o: grovnik.h grovnik.cpp
	g++ $(CPPFLAGS) -c grovnik.cpp

terrain.o: terrain.h terrain.cpp
	g++ $(CPPFLAGS) -c terrain.cpp
clean:
	rm *.o frupal

run:
	make && ./frupal
