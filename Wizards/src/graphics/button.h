#ifndef BUTTON_H
#define BUTTON_H

#include "element.h"
#include <string>

using namespace std;

class Button: public WindowElement {
  public:
    Button(string title, float widthPercent = 0.3): WindowElement(3, widthPercent) {
      this->title = title;
  }
    void setTitle(string title) {
      this->title = title;
      paint();
  }
    void paint() override {
      for (int i = 0; i < width; i++) {
          drawText("─", x + i, y, (selected ? CYAN : state));
          drawText(" ", x + i, y + 1);
          drawText("─", x + i, y + 2, (selected ? CYAN : state));
      }
      drawText("╭", x, y, (selected ? CYAN : state));
      drawText("╮", x + width, y, (selected ? CYAN : state));
      drawText("│", x, y + 1, (selected ? CYAN : state));
      drawText("│", x + width, y + 1, (selected ? CYAN : state));
      drawText("╰", x, y + 2, (selected ? CYAN : state));
      drawText("╯", x + width, y + 2, (selected ? CYAN : state));
      
      int titleX = x + (width / 2) - (title.length() / 2);
      drawText(title, titleX, y + 1, (selected ? CYAN : state));
  }
    void click() {
      setSelected(true);

      string line;
      getline(cin, line);
      setSelected(false);
  }

  private:
    string title;
    void (*onClick)() = NULL;
};

#endif