#ifndef WINDOW_ELEMENT_H
#define WINDOW_ELEMENT_H

#include <string>
#include <iostream>
#include "util.h"

using namespace std;

const Style DEFUALT = WHITE;
const Style DISABLED = DIM;
const Style SUCCESS = GREEN;
const Style ERROR = RED;

class WindowElement {
  public:
    WindowElement(int height, float widthPercent) {
      this->height = height;
      this->widthPercent = widthPercent;
      this->selected = false;
    }

    ~WindowElement() {}

    virtual void paint() {
      cout << "AHHHHH";
    }
    
    void setWidthPercent(double widthPercent) {
      this->widthPercent = widthPercent;
    }

    void setSelected(bool selected) {
      this->selected = selected;
      this->paint();
    }

    void setLocation(int x, int y, int width) {
      this->x = x;
      this->y = y;
      this->width = width;
    }

    void setState(Style state) {
      this->state = state;
      this->paint();
    }

    void setHidden(bool hidden) {
      this->hidden = hidden;
      this->paint();
    }

    double widthPercent;
    double height;
    bool selected;
    bool hidden = false;
    int x = 0, y = 0, width = 0;
    Style state = DEFUALT;
};

#endif