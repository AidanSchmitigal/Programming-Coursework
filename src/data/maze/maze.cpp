#include "maze.h"

#include <cstddef>

using namespace std;

Maze::Maze(int width, int height) {
    this->width = width;
    this->height = height;
    locations = vector<vector<MazeRoom*>>(width, vector<MazeRoom*>(height, NULL));
}

Maze::~Maze() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            delete locations[i][j];
        }
    }
}

MazeRoom* Maze::getRoom(int x, int y) {
    return locations[x][y];
}

void Maze::setRoom(int x, int y, MazeRoom* room) {
    delete locations[x][y];
    locations[x][y] = room;
}

void Maze::generate() {}
