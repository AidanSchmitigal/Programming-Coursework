#include "room.h"

#include <algorithm>

using namespace std;

MazeRoom::MazeRoom() {
    occupied = false;
}
MazeRoom::MazeRoom(int x, int y) {
    occupied = false;
    this->x = x;
    this->y = y;
}

int MazeRoom::getX() {
    return x;
}

int MazeRoom::getY() {
    return y;
}

void MazeRoom::addPerson(MazePerson* person) {
    people.push_back(person);
    occupied = true;
}
void MazeRoom::removePerson(MazePerson* person) {
    people.erase(remove(people.begin(), people.end(), person), people.end());
    occupied = false;
}

bool MazeRoom::isOccupied() {
    return occupied;
}
