#ifndef MAZE_ROOM_H
#define MAZE_ROOM_H

#include <string>
#include <vector>

#include "../peoples/person.h"

using namespace std;

class MazeRoom {
   public:
    MazeRoom(int x, int y);
    virtual ~MazeRoom();

    /*********************************************************************
    ** Function: getX
    ** Description: Gets the x coordinate of the room
    ** Parameters: None
    ** Pre-Conditions: None
    ** Post-Conditions: Returns the x coordinate of the room
    *********************************************************************/
    int getX();
    /*********************************************************************
     ** Function: getY
     ** Description:     Gets the y coordinate of the room
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Returns the y coordinate of the room
     *********************************************************************/
    int getY();

    /*********************************************************************
    ** Function: isOccupied
    ** Description: Returns whether or not the room is occupied
    ** Parameters: None
    ** Pre-Conditions: None
    ** Post-Conditions: Returns whether or not the room is occupied
    *********************************************************************/
    virtual bool isOccupied() = 0;
    /*********************************************************************
     ** Function: isOccupiable
     ** Description: Returns whether or not the room is occupiable
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Returns whether or not the room is occupiable
     *********************************************************************/
    virtual bool isOccupiable() = 0;
    /*********************************************************************
     ** Function: getDisplayChar
     ** Description:      Returns the character to display for the room
     ** Parameters:  None
     ** Pre-Conditions: None
     ** Post-Conditions: Returns the character to display for the room
     *********************************************************************/
    virtual string getDisplayChar() = 0;

   protected:
    int x;
    int y;
};

#endif