#ifndef SPACER_H
#define SPACER_H

#include "element.h"

class Spacer: public WindowElement {
  public:
    Spacer(int height) : WindowElement(height, 0.0) {}
    void paint() override {};
};

#endif