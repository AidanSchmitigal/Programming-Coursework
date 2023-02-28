#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "person.h"

class Instructor : public MazePerson {
   public:
    Instructor(int x, int y);
    bool battle();
};

#endif