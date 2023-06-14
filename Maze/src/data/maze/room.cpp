#include "room.h"

#include <algorithm>

using namespace std;

MazeRoom::MazeRoom(int x, int y) : x(x), y(y) {}

MazeRoom::~MazeRoom() {}

int MazeRoom::getX() {
    return x;
}

int MazeRoom::getY() {
    return y;
}