#include "person.h"

MazePerson::MazePerson(int x, int y) {
    this->x = x;
    this->y = y;
    this->skill = 0;
}

MazePerson::~MazePerson() {}

int MazePerson::getX() {
    return x;
}

int MazePerson::getY() {
    return y;
}

int MazePerson::getSkill() {
    return skill;
}

void MazePerson::addSkill() {
    skill++;
}

void MazePerson::setX(int x) {
    this->x = x;
}

void MazePerson::setY(int y) {
    this->y = y;
}