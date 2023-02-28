#ifndef MAZE_H
#define MAZE_H

#include <vector>

#include "../peoples/instructor.h"
#include "../peoples/ta.h"
#include "room.h"

using namespace std;

class Maze {
   public:
    Maze(int, int);
    ~Maze();

    MazeRoom* getRoom(int, int);
    void setRoom(int, int, MazeRoom*);

    void generate();

   private:
    int width;
    int height;
    vector<vector<MazeRoom*>> locations;
    vector<TA*> tas;
    Instructor* instructor;

    vector<MazeRoom*> getNeighbors(MazeRoom*);
    MazeRoom* getRandomNeighbor(MazeRoom*);
};

#endif