frupal: main.cpp
	g++ main.cpp grovnik.cpp frupal.cpp hero.cpp -Werror -Wall -lncurses -o frupal

clean:
	rm frupal

run:
	make && ./frupal
