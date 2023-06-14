#include "student.h"

Student::Student(int x, int y) : MazePerson(x, y) {}

Student::~Student() {}

bool Student::battle() {
    return true;
}

string Student::getDisplayChar() {
    return "🎒";
}