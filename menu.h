#ifndef MENU_HELPERS_H
#define MENU_HELPERS_H

#include <cstring>
#include <ncurses.h>

//Ratio of viewport width to terminal window width.
//Also defines the leftmost edge of the menu.
#define viewPortRatio 0.65

namespace menu {
// Clears menu between start/end.
// If end isn't given, instead clears from start to the line above the Energy: display at the bottom of the menu.
void clearLines(int start, int end = -1);

// Displays text in the menu
// row is the y index where to start displaying text.
// offset is the x index to start displaying text.
//
// If text is too large to fit on a single line, it will wrap to the next row.
// Newline characters in text will push the following text to the next row.
// Text on all lines is indented to the offset.
//
// ROW will be increased to point to the y index immediately below the end of the displayed text.
void displayStat(int &row, const char *text, int offset = 1); 

} // namespace menu
#endif
