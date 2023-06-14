#ifndef MAZE_H
#define MAZE_H

#include <vector>

#include "../../TerminalGraphics.h"
#include "../peoples/instructor.h"
#include "../peoples/skill.h"
#include "../peoples/student.h"
#include "../peoples/ta.h"
#include "openspace.h"
#include "room.h"

using namespace std;

class Maze {
   public:
    Maze(int, bool useAI = false);
    ~Maze();

    /*********************************************************************
     ** Function: getRoom
     ** Description: Gets the room at the given coordinates
     ** Parameters: int x, int y
     ** Pre-Conditions: x and y are valid coordinates
     ** Post-Conditions: Returns the room at the given coordinates
     *********************************************************************/
    MazeRoom* getRoom(int, int);
    /*********************************************************************
     ** Function: getRoom
     ** Description: Gets the room that the given person is in
     ** Parameters: MazePerson* person
     ** Pre-Conditions: person is a valid person
     ** Post-Conditions: Returns the room that the given person is in
     *********************************************************************/
    MazeOpenSpace* getRoom(MazePerson*);
    /*********************************************************************
     ** Function: setRoom
     ** Description: Sets the room at the given coordinates
     ** Parameters: int x, int y, MazeRoom* room
     ** Pre-Conditions: x and y are valid coordinates
     ** Post-Conditions: Sets the room at the given coordinates
     *********************************************************************/
    void setRoom(int, int, MazeRoom*);

    /*********************************************************************
     ** Function: moveStudent
     ** Description: Moves the student in the given direction
     ** Parameters: ArrowKey direction
     ** Pre-Conditions: direction is a valid direction
     ** Post-Conditions: Moves the student in the given direction
     *********************************************************************/
    MazePerson* moveStudent(ArrowKey);
    /*********************************************************************
     ** Function: moveTAs
     ** Description: Moves the TAs
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Moves the TAs
     *********************************************************************/
    TA* moveTAs();

    /*********************************************************************
     ** Function: removeSkill
     ** Description: Removes a skill from the maze
     ** Parameters: Skill* skill
     ** Pre-Conditions: skill is a valid skill
     ** Post-Conditions: Removes a skill from the maze
     *********************************************************************/
    void removeSkill(Skill*);
    /*********************************************************************
     ** Function: removeTA
     ** Description: Adds a TA to the maze
     ** Parameters: TA* ta
     ** Pre-Conditions: ta is a valid TA
     ** Post-Conditions: Adds a TA to the maze
     *********************************************************************/
    void removeTA(TA*);

    /*********************************************************************
     ** Function: generate
     ** Description: Generates the maze
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Generates the maze
     *********************************************************************/
    void generate();

    /*********************************************************************
     ** Function: getSize
     ** Description: Gets the size of the maze
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Gets the size of the maze
     *********************************************************************/
    int getSize();
    /*********************************************************************
     ** Function: getStudent
     ** Description: Gets the student
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Gets the student
     *********************************************************************/
    Student* getStudent();
    /*********************************************************************
     ** Function: get NumSkills
     ** Description: Gets the number of skills
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Gets the number of skills
     *********************************************************************/
    int getNumSkills();
    /*********************************************************************
     ** Function: getNumTAs
     ** Description: Gets the number of TAs
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Gets the number of TAs
     *********************************************************************/
    int getNumTAs();
    /*********************************************************************
     ** Function: usingAI
     ** Description: Returns whether or not the maze is using AI
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Returns whether or not the maze is using AI
     *********************************************************************/
    bool usingAI();

   private:
    int size;
    bool useAI;
    vector<vector<MazeRoom*>> locations;
    vector<Skill*> skills;
    vector<TA*> tas;
    Instructor* instructor;
    Student* student;

    vector<MazeRoom*> getNeighbors(MazeRoom*);
    MazeRoom* getRandomNeighbor(MazeRoom*);
    MazeRoom* getNeighborInDirection(MazeRoom*, ArrowKey);
    MazeOpenSpace* getRandomUnoccupied();
};

class MazeElement : public WindowElement {
   public:
    MazeElement();

    tuple<int, int> getFixedSize(int parentWidth, int parentHeight) override;

    void paint(int x, int y, int width, int height) override;

    void arrowKeyEvent(ArrowKey key, WindowElement* element) override;
};

#endif