#ifndef MENU_HELPERS_H
#define MENU_HELPERS_H

#include <cstring>
#include <ncurses.h>

#define viewPortRatio 0.65

namespace menu {
// clears menu between start/end
// if end isn't given, instead clears between start and the Energy: display
void clearLines(int start, int end = -1);
void displayStat(int &row, const char *text, int offset = 1); // displays info

} // namespace menu
#endif
