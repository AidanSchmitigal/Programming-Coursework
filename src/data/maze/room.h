#ifndef MAZE_ROOM_H
#define MAZE_ROOM_H

#include <vector>

#include "../peoples/person.h"

using namespace std;

class MazeRoom {
   public:
    MazeRoom();
    MazeRoom(int x, int y);

    int getX();
    int getY();

    void addPerson(MazePerson* person);
    void removePerson(MazePerson* person);

    bool isOccupied();

   protected:
    vector<MazePerson*> people;
    bool occupied;
    int x;
    int y;
};

#endif