CPPFLAGS = -g -Wall -Werror

frupal: grovnik.o frupal.o hero.o main.o
	g++ $(CPPFLAGS) main.o frupal.o grovnik.o hero.o -o frupal -lncurses
  
main.o: main.cpp
	g++ -g -c main.cpp
  
hero.o: frupal.h hero.cpp
	g++ -g -c hero.cpp
  
frupal.o: frupal.h frupal.cpp
	g++ -g -c frupal.cpp

grovnik.o: grovnik.h grovnik.cpp
	g++ -g -c grovnik.cpp
  
clean:
	rm *.o frupal

run:
	make && ./frupal