#ifndef WALL_H
#define WALL_H

#include "room.h"

class MazeWall : public MazeRoom {
   public:
    MazeWall(int x, int y);
    ~MazeWall();

    /*********************************************************************
    ** Function: isOccupied
    ** Description: Returns whether or not the room is occupied
    ** Parameters: None
    ** Pre-Conditions: None
    ** Post-Conditions: Returns whether or not the room is occupied
    *********************************************************************/
    bool isOccupied() override;
    /*********************************************************************
     ** Function: isOccupiable
     ** Description: Returns whether or not the room is occupiable
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions: Returns whether or not the room is occupiable
     *********************************************************************/
    bool isOccupiable() override;
    /*********************************************************************
     ** Function: getDisplayChar
     ** Description: Returns the character to display for the room
     ** Parameters: None
     ** Pre-Conditions: None
     ** Post-Conditions:     Returns the character to display for the room
     *********************************************************************/
    string getDisplayChar() override;
};

#endif