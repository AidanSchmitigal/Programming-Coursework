#include "wall.h"

MazeWall::MazeWall() {
    occupied = true;
}
MazeWall::MazeWall(int x, int y) {
    occupied = true;
    this->x = x;
    this->y = y;
}

bool MazeWall::isOccupied() {
    return true;
}