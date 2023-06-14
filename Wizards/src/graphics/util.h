#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>

using namespace std;

enum Style {
  RESET = 0,
  BOLD = 1,
  DIM = 2,
  UNDERLINED = 4,
  BLINK = 5,
  REVERSE = 7,
  HIDDEN = 8,
  BLACK = 30,
  RED = 31,
  GREEN = 32,
  YELLOW = 33,
  BLUE = 34,
  MAGENTA = 35,
  CYAN = 36,
  WHITE = 37,
  BRIGHT_CYAN = 96,
};
string getColor(int color);
void drawText(string text, int x, int y, int color = WHITE);

string toCapitalCase(string text);

void setCursorPosition(int x, int y);
void showCursor();
void hideCursor();

#endif