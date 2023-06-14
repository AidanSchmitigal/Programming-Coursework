#ifndef SPELLBOOK_ELEMENT_H
#define SPELLBOOK_ELEMENT_H

#include <iostream>
#include "element.h"
#include "util.h"
#include "../data/spellbook.h"

using namespace std;

class SpellbookElement: public WindowElement {
  public:
    SpellbookElement(Spellbook spellbook, bool showSpells, float widthPercent = 0.8): WindowElement(2, widthPercent) {
        this->spellbook = spellbook;
        this->showSpells = showSpells;
    }
    void paint() override {
        for (int i = 1; i < width - 1; i++) {
            drawText("·", x + i, y + 1);
            drawText("·", x + i, y + height - 2);
        }
        
        drawText("╭┬─┤", x, y);
        drawText("╰┴─┤", x, y + height - 1);
        
        drawText("├─┬╮", x + width - 4, y);
        drawText("├─┴╯", x + width - 4, y + height - 1);

        drawText(toCapitalCase(spellbook.title), x + 5, y);
        drawText("By " + toCapitalCase(spellbook.author), x + 5, y + 1);
        drawText("Pages: " + to_string(spellbook.numPages), x + width - 12 - to_string(spellbook.numPages).length(), y);
        drawText("Edition: " + to_string(spellbook.edition), x + width - 14 - to_string(spellbook.edition).length(), y + 1);
    }
  private:
    struct Spellbook spellbook;
    bool showSpells;

};

#endif