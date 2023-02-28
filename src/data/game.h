#ifndef GAME_H
#define GAME_H

#include "maze/maze.h"
#include "peoples/person.h"

class Game {
   public:
    Game();
    ~Game();

    static Game* getInstance();

    static const int NUM_WALLS = 4;
    static const int NUM_TAS = 4;
    static const int NUM_SKILL = 4;

    void init();
    void run();

    MazePerson* getPlayer();

    void setMaze(Maze*);
    Maze* getMaze();

   private:
    static Game* instance;

    Maze* maze;
    MazePerson* player;
};

#endif