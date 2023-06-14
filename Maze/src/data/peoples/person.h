#ifndef MAZE_PERSON_H
#define MAZE_PERSON_H

#include <string>

using namespace std;

class MazePerson {
   public:
    MazePerson(int x, int y);
    virtual ~MazePerson();

    /*********************************************************************
    ** Function: getX
    ** Description: Gets the x coordinate of the person
    ** Parameters: None
    ** Pre-Conditions: None
    ** Post-Conditions: Returns the x coordinate of the person
    *********************************************************************/
    int getX();
    /*********************************************************************
     ** Function: getY
     ** Description:   Gets the y coordinate of the person
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Returns the y coordinate of the person
     *********************************************************************/
    int getY();
    /*********************************************************************
     ** Function: getSkill
     ** Description: Gets the skill of the person
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions:  Returns the skill of the person
     *********************************************************************/
    int getSkill();
    /*********************************************************************
     ** Function: addSkill
     ** Description: Adds a skill to the person
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Adds a skill to the person
     *********************************************************************/
    void addSkill();

    /*********************************************************************
    ** Function: setX
    ** Description: Sets the x coordinate of the person
    ** Parameters: int x
    ** Pre-Conditions: x is a valid coordinate
    ** Post-Conditions: Sets the x coordinate of the person
    *********************************************************************/
    void setX(int x);
    /*********************************************************************
     ** Function: setY
     ** Description: Sets the y coordinate of the person
     ** Parameters: int y
     ** Pre-Conditions: y is a valid coordinate
     ** Post-Conditions: Sets the y coordinate of the person
     *********************************************************************/
    void setY(int y);

    /*********************************************************************
    ** Function: move
    ** Description: Moves the person
    ** Parameters: None
    ** Pre-Conditions: None
    ** Post-Conditions: Moves the person
    *********************************************************************/
    void move();
    /*********************************************************************
     ** Function: battle
     ** Description: Returns whether or not the person won the battle
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Returns whether or not the person won the battle
     *********************************************************************/
    virtual bool battle() = 0;
    /*********************************************************************
     ** Function: getDisplayChar
     ** Description: Returns the character to display for the person
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Returns the character to display for the person
     *********************************************************************/
    virtual string getDisplayChar() = 0;

   private:
    int x;
    int y;
    int skill;
};

#endif