#include "frupal.h"
#include "menu.h"

int main(int argc, char **argv) {
  char ch = ' ';
  while (ch != 'q') {
    initscr(); // Inits screen / sets up ncurses
    noecho();
    cbreak();

    int y, x; // height + width are the size of the ncurses window we want. y +
              // x are the size of the entire terminal
    getmaxyx(stdscr, y, x); // Initialize y + x with the appropriate values for
                            // the screen / terminal's current size
                            //
    // Create a new window y lines high, and a percentage of x columns wide, as described by the standard screen (terminal window size)
    WINDOW *mapwin = newwin(y, x * viewPortRatio, 0, 0);

    // vertical line separating menu and map
    move(0, x * viewPortRatio);
    vline('#', y);

    Frupal *g;
    bool goodMapFile = false;
    // Attempt to load the map from a file if one was provided as a command line
    // argument.
    if (argc > 1) {
      g = new Frupal(mapwin, argv[1]);
      goodMapFile = g->mapLoaded();
      if (!goodMapFile)
        delete g;
    }

    // If we were not given a map file, drop the player into a limbo of empty meadows.
    // XXX refactor opportunity: should this instead display usage information and exit?
    if (!goodMapFile) {
      g = new Frupal(mapwin, 5, 5);
    }
    start_color(); // start ncurses color

    // series of inits initializes our color pairs for drawing the map
    init_pair(1, COLOR_YELLOW, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_BLUE);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_BLACK, COLOR_GREEN);
    init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_CYAN);
    init_pair(8, COLOR_CYAN, COLOR_WHITE);
    init_pair(9, COLOR_RED, COLOR_BLACK);
    init_pair(10, COLOR_BLACK, COLOR_RED);
    init_pair(11, COLOR_BLACK, COLOR_YELLOW);

    bkgd(COLOR_PAIR(6));
    refresh();
    g->showMap();
    wrefresh(mapwin);
    curs_set(0);

    int cursorX = 0, cursorY = 0;
    while (ch != 'q' && ch != 'r') {
      getyx(mapwin, cursorY, cursorX); // Remember cursor position
      int row = 0;

      // Print out instructions to the menu
      menu::displayStat(row, "WASD Keys to Move Hero", 1);
      menu::displayStat(row, "Arrow Keys to Look Around", 1);
      move(cursorY, cursorX); // DisplayStat moved the cursor, put it back where
                              // it started.
      refresh();
      ch = g->getmv();
    }
    if (ch == 'r')
      ch = ' ';

    endwin(); // Ends ncurses / deallocates memory

    delete g;
  }

  return 0;
}
