#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <tuple>
#include <vector>
#include <string>
#include "element.h"

using namespace std;

class Window {
  public:
    Window(int, string = "", bool = false);

    void setWidthFR(int);

    void drawBorder();
    void drawCenteredText(string);
    void setTitle(string);
    void addElement(WindowElement*, int spacer = 0);
    WindowElement* getElement(int);
    void removeElement(WindowElement*);
    void removeAllElements();

    void setHidden(bool);
    void clear();

    static void checkScreenSize();
    static void prepareScreen();
    static void exit();

  private:
    int getWidthFR();
    int getWidth();
    int getXFR();
    int getX();
    int getTotalWidthFR();

    static struct winsize w;
    static void updateWinSize();
    static void paint();

    bool hidden;
    int width, index;
    static int minWidth, minHeight, totalWindows;
    static vector<Window*> windows;

    string title;
    vector<WindowElement*> elements = vector<WindowElement*>();
};

#endif