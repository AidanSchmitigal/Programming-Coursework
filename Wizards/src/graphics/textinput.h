#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <string>

#include "element.h"

using namespace std;

class TextInput : public WindowElement {
 public:
  TextInput(string title, string templateText, float widthPercent = 0.6) : WindowElement(3, widthPercent) {
    this->title = title;
    this->templateText = templateText;
  }
  
  // ~TextInput() {} < not needed if virtual on parent

  void setTitle(string title) {
    this->title = title;
    paint();
  }
  void setText(string text) {
    this->text = text;
    paint();
  }
  void paint() override {
    for (int i = 0; i < width; i++) {
      drawText("─", x + i, y, state);
      drawText(" ", x + i, y + 1, state);
      drawText("─", x + i, y + 2, state);
    }
    if (selected) {
      drawText(title, x + 2, y, CYAN);
    } else {
      drawText(title, x + 2, y, state);
    }
    drawText("╭┤", x, y, state);
    drawText("├", x + 2 + title.length(), y, state);
    if (text.length() > 0) {
      drawText(text, x + 2, y + 1, state);
    } else {
      drawText(templateText, x + 2, y + 1, DIM);
    }
    drawText("╮", x + width, y, state);
    drawText("│ ", x, y + 1, state);
    drawText("│", x + width, y + 1, state);
    drawText("╰", x, y + 2, state);
    drawText("╯", x + width, y + 2, state);
    cout << flush;
  }
  string getInput() {
    setSelected(true);

    showCursor();
    string output;
    setCursorPosition(x + 2, y + 1);
    getline(cin, output); // <

    setText(output);
    hideCursor();
    setSelected(false);

    return output;
  }

 private:
  string title;
  string text = "";
  string templateText;
};

#endif