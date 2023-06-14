#include "skill.h"

#include <cstdlib>

Skill::Skill(int x, int y) : MazePerson(x, y) {}

Skill::~Skill() {}

bool Skill::battle() {
    return false;
}

string Skill::getDisplayChar() {
    return "💾";
}