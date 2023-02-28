#ifndef TA_H
#define TA_H

#include "person.h"

class TA : public MazePerson {
   public:
    TA(int x, int y);

    bool battle();
};

#endif
