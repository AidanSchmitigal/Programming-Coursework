#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "element.h"

using namespace std;

class Text : public WindowElement {
 public:
  Text(string text, float widthPercent = 0.5) : WindowElement(1, widthPercent) {
    this->text = text;

    for (int i = 0; i < text.length(); i++) {
      if (text[i] == '\n') {
        height++;
      }
    }
  }

  void setText(string text) {
    this->text = text;
    paint();
  }

  void paint() override {
    int line = 0;
    int start = 0;
    int end = 0;
    while (end != string::npos) {
      end = text.find('\n', start);
      if (widthPercent == 0) {
        drawText(text.substr(start, end - start), x + (width - text.substr(start, end - start).length()) / 2, y + line, state);
      } else {
        drawText(text.substr(start, end - start), x, y + line, state);
      }
      start = end + 1;
      line++;
    }
  };

 private:
  string text = "";
};

#endif