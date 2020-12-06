CPPFLAGS = -g -Wall -Werror

frupal: grovnik.o terrain.o frupal.o hero.o main.o menu.o
	g++ $(CPPFLAGS) main.o frupal.o hero.o grovnik.o terrain.o menu.o -o frupal -lncurses -ltinfo
  
main.o: main.cpp menu.h
	g++ $(CPPFLAGS) -c main.cpp
  
hero.o: hero.h hero.cpp menu.h
	g++ $(CPPFLAGS) -c hero.cpp
  
frupal.o: frupal.h frupal.cpp menu.h
	g++ $(CPPFLAGS) -c frupal.cpp
  
grovnik.o: grovnik.h grovnik.cpp
	g++ $(CPPFLAGS) -c grovnik.cpp

terrain.o: terrain.h terrain.cpp menu.h
	g++ $(CPPFLAGS) -c terrain.cpp

menu.o: menu.h menu.cpp
	g++ $(CPPFLAGS) -c menu.cpp

clean:
	rm *.o frupal

run:
	make && ./frupal

test: grovnik.o terrain.o frupal.o hero.o main.o menu.o
	g++ $(CPPFLAGS) frupal.o hero.o grovnik.o terrain.o menu.o tests.cpp -o testEXE -lncurses -ltinfo -lgtest

