#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"

class Student : public MazePerson {
   public:
    Student(int x, int y);
    ~Student() override;

    /*********************************************************************
    ** Function: battle
    ** Description: Returns whether or not the person won the battle
    ** Parameters: None
    ** Pre-Conditions: None
    ** Post-Conditions: Returns whether or not the person won the battle
    *********************************************************************/
    bool battle() override;
    /*********************************************************************
     ** Function:    getDisplayChar
     ** Description: Returns the character to display for the person
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Returns the character to display for the person
     *********************************************************************/
    string getDisplayChar() override;
};

#endif