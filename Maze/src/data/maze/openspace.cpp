#include "openspace.h"

using namespace std;

MazeOpenSpace::MazeOpenSpace(int x, int y) : MazeRoom(x, y) {}

MazeOpenSpace::~MazeOpenSpace() {}

bool MazeOpenSpace::isOccupied() {
    return people.size() > 0;
}

bool MazeOpenSpace::isOccupiable() {
    return true;
}

string MazeOpenSpace::getDisplayChar() {
    string display = "";
    for (int i = 0; i < people.size(); i++) {
        display += people[i]->getDisplayChar();
    }

    return display;
}

void MazeOpenSpace::addPerson(MazePerson* person) {
    if (isOccupiable())
        people.push_back(person);
}

void MazeOpenSpace::removePerson(MazePerson* person) {
    people.erase(remove(people.begin(), people.end(), person), people.end());
}

MazePerson* MazeOpenSpace::getPerson(int index) {
    return people[index];
}

vector<MazePerson*> MazeOpenSpace::getPeople() {
    return people;
}