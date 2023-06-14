#ifndef LOCK_H
#define LOCK_H

#include "element.h"

using namespace std;

class Lock: public WindowElement {
  public:
    Lock() : WindowElement(15, 0.0) {
        locked = true;
    }
    void paint() override {
        if (locked) {
            drawText("     .--------.     ",   x - 11, y);
            drawText("    / .------. \\    ",  x - 11, y + 1);
            drawText("   / /        \\ \\   ", x - 11, y + 2);
            drawText("   | |        | |   ",   x - 11, y + 3);
            drawText("  _| |________| |_  ",   x - 11, y + 4);
            drawText(".' |_|        |_| '.",   x - 11, y + 5);
            drawText("'._____ ____ _____.'",   x - 11, y + 6);
            drawText("|     .'____'.     |",   x - 11, y + 7);
            drawText("'.__.'.'    '.'.__.'",   x - 11, y + 8);
            drawText("'.__  |      |  __.'",   x - 11, y + 9);
            drawText("|   '.'.____.'.'   |",   x - 11, y + 10);
            drawText("'.____'.____.'____.'",   x - 11, y + 11);
            drawText("'.________________.'",   x - 11, y + 12);

            drawText(lockedMessage, x - (lockedMessage.length() / 2), y + 14);

        }
    }
    void setLockedMessage(string message) {
        lockedMessage = message;
        paint();
    }
    void setLocked(bool locked) {
        this->locked = locked;
        paint();
    }

    private:
        bool locked;
        string lockedMessage = "";
};

#endif