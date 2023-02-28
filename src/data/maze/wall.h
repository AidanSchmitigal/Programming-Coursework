#ifndef WALL_H
#define WALL_H

#include "room.h"

class MazeWall : public MazeRoom {
   public:
    MazeWall();
    MazeWall(int x, int y);

    bool isOccupied();
};

#endif