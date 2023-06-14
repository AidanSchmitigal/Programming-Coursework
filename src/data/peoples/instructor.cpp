#include "instructor.h"

Instructor::Instructor(int x, int y) : MazePerson(x, y) {}

Instructor::~Instructor() {}

bool Instructor::battle() {
    return true;
}

string Instructor::getDisplayChar() {
    return "💻";
}