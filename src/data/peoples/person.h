#ifndef MAZE_PERSON_H
#define MAZE_PERSON_H

class MazePerson {
   public:
    MazePerson(int x, int y);

    int getX();
    int getY();
    int getSkill();

    void setX(int x);
    void setY(int y);

    void move();
    virtual bool battle() = 0;

   private:
    int x;
    int y;
    int skill;
};

#endif