#ifndef OPENSPACE_H
#define OPENSPACE_H

#include <algorithm>

#include "room.h"

class MazeOpenSpace : public MazeRoom {
   public:
    MazeOpenSpace(int x, int y);
    ~MazeOpenSpace();

    /*********************************************************************
    ** Function: addPerson
    ** Description: Adds a person to the room
    ** Parameters: MazePerson* person
    ** Pre-Conditions: person is a valid person
    ** Post-Conditions: Adds a person to the room
    *********************************************************************/
    void addPerson(MazePerson* person);
    /*********************************************************************
     ** Function: removePerson
     ** Description: Removes a person from the room
     ** Parameters: MazePerson* person
     ** Pre-Conditions: person is a valid person
     ** Post-Conditions: Removes a person from the room
     *********************************************************************/
    void removePerson(MazePerson* person);
    /*********************************************************************
     ** Function: getPerson
     ** Description: Gets a person from the room
     ** Parameters: int index
     ** Pre-Conditions: index is a valid index
     ** Post-Conditions: Gets a person from the room
     *********************************************************************/
    MazePerson* getPerson(int index);
    /*********************************************************************
     ** Function: getPeople
     ** Description: Gets all the people in the room
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Gets all the people in the room
     *********************************************************************/
    vector<MazePerson*> getPeople();

    /*********************************************************************
    ** Function: isOccupied
    ** Description: Returns whether or not the room is occupied
    ** Parameters: None
    ** Pre-Conditions: None
    ** Post-Conditions: Returns whether or not the room is occupied
    *********************************************************************/
    bool isOccupied() override;
    /*********************************************************************
     * Function: isOccupiable
     * Description: Returns whether or not the room is occupiable
     * Parameters: None
     * Pre-Conditions: None
     * Post-Conditions: Returns whether or not the room is occupiable
     * *******************************************************************/
    bool isOccupiable() override;
    /*********************************************************************
     * Function: getDisplayChar
     * Description: Returns the display character for the room
     * Parameters: None
     * Pre-Conditions: None
     * Post-Conditions: Returns the display character for the room
     * *******************************************************************/
    string getDisplayChar() override;

   private:
    vector<MazePerson*> people;
};

#endif