#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "person.h"

class Instructor : public MazePerson {
   public:
    Instructor(int x, int y);
    ~Instructor() override;

    /*********************************************************************
    ** Function: battle
    ** Description: Returns whether or not the person won the battle
    ** Parameters: None
    ** Pre-Conditions: None
    ** Post-Conditions: Returns whether or not the person won the battle
    *********************************************************************/
    bool battle() override;
    /*********************************************************************
     ** Function: getDisplayChar
     ** Description: Returns the character to display for the person
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Returns the character to display for the person
     *********************************************************************/
    string getDisplayChar() override;
};

#endif