frupal: main.cpp
	g++ main.cpp frupal.cpp hero.cpp -Werror -Wall -lncurses -ltinfo -o frupal

clean:
	rm frupal

run:
	make && ./frupal
