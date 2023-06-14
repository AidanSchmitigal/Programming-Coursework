#ifndef GAME_H
#define GAME_H

#include "leaderboard.h"
#include "maze/maze.h"
#include "peoples/instructor.h"
#include "peoples/skill.h"
#include "peoples/ta.h"
#include "program/program.h"

class Game {
   public:
    ~Game();
    static Game* getInstance();

    static const int NUM_WALLS = 4;
    static const int NUM_TAS = 3;
    static const int NUM_SKILLS = 6;

    /*********************************************************************
     ** Function: getMaze
     ** Description: Returns the maze
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Returns the maze
     *********************************************************************/
    Maze* getMaze();
    /*********************************************************************
     ** Function: getSize
     ** Description: Returns the size of the maze
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Returns the size of the maze
     *********************************************************************/
    void setSize(int);

    /*********************************************************************
    ** Function: start
    ** Description: Starts the game
    ** Parameters: bool useAI
    ** Pre-Conditions: None
    ** Post-Conditions: Starts the game
    *********************************************************************/
    void start(bool useAI = false);
    /*********************************************************************
     ** Function: moveStudent
     ** Description: Moves the student in the given direction
     ** Parameters: ArrowKey direction
     ** Pre-Conditions: direction is a valid direction
     ** Post-Conditions: Moves the student in the given direction
     *********************************************************************/
    void moveStudent(ArrowKey direction);
    /*********************************************************************
     ** Function: step
     ** Description: Steps the game
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Steps the game
     *********************************************************************/
    void step();

    void addStudentSkill(Skill* skill);
    void beatTA(TA* ta);

    Program* getProgram(int level);

    void switchToStartScreen();
    void switchToLeaderboardScreen();
    void switchToGameScreen();
    void switchToBattleScreen(Skill* skill);
    void switchToBattleScreen(TA* ta);
    void switchToBattleScreen(Instructor* instructor);
    void switchToInstructionsScreen();
    void switchToEndScreen(bool win, vector<string> text);

   private:
    Game();

    static Game* instance;

    Maze* maze;
    int size;
    Program* currentProgram = NULL;
    Leaderboard* leaderboard = NULL;
};

#endif