#ifndef USER_WELCOME_H
#define USER_WELCOME_H

#include <iostream>
#include "element.h"
#include "util.h"
#include "../data/wizard.h"

using namespace std;

class UserWelcome: public WindowElement {
  public:
    UserWelcome(Wizard wizard, float widthPercent = 0.8): WindowElement(6, widthPercent) {
        this->wizard = wizard;
    }
    void paint() override {
        // Draw Rounded Rectangle like window With text in the middle
        drawText("╭", x, y);
        drawText("╰", x, y + height - 1);
        
        drawText("╮", x + width - 1, y);
        drawText("╯", x + width - 1, y + height - 1);

        // Draw top & bottom border
        for (int i = 1; i < width - 1; i++) {
            drawText("─", x + i, y);
            drawText("─", x + i, y + height - 1);
        }

        // Draw side borders
        for (int i = 1; i < height - 1; i++) {
            drawText("│", x, y + i);
            drawText("│", x + width - 1, y + i);
        }

        drawText("Welcome " + toCapitalCase(wizard.name) + "!", x + 2, y + 1);
        drawText("ID: " + to_string(wizard.id), x + 2, y + 2);
        drawText("Position: " + wizard.positionTitle, x + 2, y + 3);
        drawText("Beard Length: " + to_string(wizard.beardLength), x + 2, y + 4);
    }
  private:
    Wizard wizard;
};

#endif