CPPFLAGS = -g -Wall -Werror

frupal: terrain.o frupal.o hero.o main.o
	g++ $(CPPFLAGS) main.o frupal.o terrain.o hero.o -o frupal -lncurses
  
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
