#include "ta.h"

TA::TA(int x, int y) : MazePerson(x, y) {
    this->incapacitated = false;
}

TA::~TA() {}

bool TA::battle() {
    if (incapacitated) {
        return false;
    } else {
        incapacitated = true;
        return true;
    }
}

string TA::getDisplayChar() {
    return "🎓";
}