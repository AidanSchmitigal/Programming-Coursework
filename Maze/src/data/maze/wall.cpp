#include "wall.h"

MazeWall::MazeWall(int x, int y) : MazeRoom(x, y) {}

MazeWall::~MazeWall() {}

bool MazeWall::isOccupied() {
    return true;
}

bool MazeWall::isOccupiable() {
    return false;
}

string MazeWall::getDisplayChar() {
    return "";
}