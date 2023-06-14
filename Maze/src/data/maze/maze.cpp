#include "maze.h"

#include <cstddef>

#include "../game.h"
#include "openspace.h"
#include "wall.h"

using namespace std;

Maze::Maze(int size, bool useAI) {
    this->size = size;
    this->useAI = useAI;
    locations = vector<vector<MazeRoom*> >(size, vector<MazeRoom*>(size, NULL));
}

Maze::~Maze() {
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            if (locations[i][j] != NULL)
                delete locations[i][j];
        }
    }
    for (Skill* skill : skills) {
        delete skill;
    }
    for (TA* ta : tas) {
        delete ta;
    }
    delete instructor;
    delete student;
}

// Getters and setters

MazeRoom* Maze::getRoom(int x, int y) {
    return locations[x][y];
}

MazeOpenSpace* Maze::getRoom(MazePerson* person) {
    return dynamic_cast<MazeOpenSpace*>(locations[person->getX()][person->getY()]);
}

int Maze::getSize() {
    return size;
}

Student* Maze::getStudent() {
    return student;
}

int Maze::getNumSkills() {
    return skills.size();
}

int Maze::getNumTAs() {
    return tas.size();
}

bool Maze::usingAI() {
    return useAI;
}

void Maze::setRoom(int x, int y, MazeRoom* room) {
    delete locations[x][y];
    locations[x][y] = room;
}

MazeOpenSpace* Maze::getRandomUnoccupied() {
    int x = rand() % size;
    int y = rand() % size;
    while (locations[x][y]->isOccupied()) {
        x = rand() % size;
        y = rand() % size;
    }
    return dynamic_cast<MazeOpenSpace*>(locations[x][y]);
}

MazeRoom* Maze::getRandomNeighbor(MazeRoom* room) {
    vector<MazeRoom*> neighbors = getNeighbors(room);
    return neighbors[rand() % neighbors.size()];
}

vector<MazeRoom*> Maze::getNeighbors(MazeRoom* room) {
    vector<MazeRoom*> neighbors;
    int x = room->getX();
    int y = room->getY();
    if (x > 0)
        neighbors.push_back(locations[x - 1][y]);
    if (x < size - 1)
        neighbors.push_back(locations[x + 1][y]);
    if (y > 0)
        neighbors.push_back(locations[x][y - 1]);
    if (y < size - 1)
        neighbors.push_back(locations[x][y + 1]);
    return neighbors;
}

MazeRoom* Maze::getNeighborInDirection(MazeRoom* room, ArrowKey key) {
    int x = room->getX();
    int y = room->getY();
    switch (key) {
        case ArrowKey::UP:
            if (y > 0) {
                return locations[x][y - 1];
            }
            break;
        case ArrowKey::DOWN:
            if (y < size - 1) {
                return locations[x][y + 1];
            }
            break;
        case ArrowKey::LEFT:
            if (x > 0) {
                return locations[x - 1][y];
            }
            break;
        case ArrowKey::RIGHT:
            if (x < size - 1) {
                return locations[x + 1][y];
            }
            break;
    }
    // If the neighboring room is out of bounds, return nullptr.
    return nullptr;
}

// Movement

MazePerson* Maze::moveStudent(ArrowKey key) {
    MazeOpenSpace* room = getRoom(student);
    if (useAI) {
        // Random move
        if (MazeOpenSpace* next = dynamic_cast<MazeOpenSpace*>(getRandomNeighbor(room))) {
            if (!next->isOccupiable()) return nullptr;
            room->removePerson(student);
            next->addPerson(student);
            student->setX(next->getX());
            student->setY(next->getY());

            // If the student is in the same room as any other person, return that person.
            for (MazePerson* person : next->getPeople()) {
                if (person != student) {
                    return person;
                }
            }
        }
    } else {
        if (MazeOpenSpace* next = dynamic_cast<MazeOpenSpace*>(getNeighborInDirection(room, key))) {
            if (!next->isOccupiable()) return nullptr;
            room->removePerson(student);
            next->addPerson(student);
            student->setX(next->getX());
            student->setY(next->getY());

            // If the student is in the same room as any other person, return that person.
            for (MazePerson* person : next->getPeople()) {
                if (person != student) {
                    return person;
                }
            }
        }
    }
    return nullptr;
}

TA* Maze::moveTAs() {
    // Moving TA's randomly
    for (TA* ta : tas) {
        MazeOpenSpace* room = getRoom(ta);
        if (MazeOpenSpace* next = dynamic_cast<MazeOpenSpace*>(getRandomNeighbor(room))) {
            if (!next->isOccupiable()) return nullptr;

            room->removePerson(ta);
            next->addPerson(ta);

            ta->setX(next->getX());
            ta->setY(next->getY());
        }
    }

    // If adjacent to student, or in same room as student, return the TA.
    for (TA* ta : tas) {
        MazeOpenSpace* room = getRoom(ta);
        // Check if the TA is in the same room as the student.
        for (MazePerson* person : room->getPeople()) {
            if (person == student) {
                return ta;
            }
        }
        // Check if the TA is adjacent to the student.
        for (MazeRoom* neighbor : getNeighbors(room)) {
            if (MazeOpenSpace* next = dynamic_cast<MazeOpenSpace*>(neighbor)) {
                for (MazePerson* person : next->getPeople()) {
                    if (person == student) {
                        return ta;
                    }
                }
            }
        }
    }

    return nullptr;
}

// Removal

void Maze::removeSkill(Skill* skill) {
    MazeOpenSpace* room = getRoom(skill);
    room->removePerson(skill);
    skills.erase(std::remove(skills.begin(), skills.end(), skill), skills.end());
    delete skill;
}

void Maze::removeTA(TA* ta) {
    MazeOpenSpace* room = getRoom(ta);
    room->removePerson(ta);
    tas.erase(std::remove(tas.begin(), tas.end(), ta), tas.end());
    delete ta;
}

// Generation

void Maze::generate() {
    // 1. Fill with empty rooms
    for (int i = 0; i < Game::NUM_WALLS; i++) {
        int x = rand() % size;
        int y = rand() % size;
        setRoom(x, y, new MazeWall(x, y));
    }

    // 2. Add walls in random locations
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (locations[i][j] == NULL)
                setRoom(i, j, new MazeOpenSpace(i, j));
        }
    }

    // 3. Randomly place NUM_TAS TAs in the maze
    for (int i = 0; i < Game::NUM_TAS; i++) {
        MazeOpenSpace* room = getRandomUnoccupied();
        tas.push_back(new TA(room->getX(), room->getY()));
        room->addPerson(tas.back());
    }

    // 4. Randomly place skill in the maze
    for (int i = 0; i < Game::NUM_SKILLS; i++) {
        MazeOpenSpace* room = getRandomUnoccupied();
        skills.push_back(new Skill(room->getX(), room->getY()));
        room->addPerson(skills.back());
    }

    // 5. Randomly place the player in the maze
    MazeOpenSpace* room = getRandomUnoccupied();
    student = new Student(room->getX(), room->getY());
    room->addPerson(student);

    // 6. Randomly place the exit in the maze
    room = getRandomUnoccupied();
    instructor = new Instructor(room->getX(), room->getY());
    room->addPerson(instructor);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MazeElement::MazeElement() : WindowElement(1.0, 1.0) {
    selectable = true;
}

tuple<int, int> MazeElement::getFixedSize(int parentWidth, int parentHeight) {
    float aspectRatio = 0.6f;
    int size = min(parentWidth * aspectRatio, (float)parentHeight);
    int boxWidth = size * 5 / 3, boxHeight = size;
    return make_tuple(boxWidth, boxHeight);
}

void MazeElement::paint(int x, int y, int width, int height) {
    float aspectRatio = 0.6f;
    Game* game = Game::getInstance();
    Maze* maze = game->getMaze();

    int mazeSize = maze->getSize();

    int size = min(width * aspectRatio, (float)height);
    int outlineWidth = size * 5 / 3, outlineHeight = size;

    setValues(x, y, outlineWidth, outlineHeight);
    drawBox(x, y, outlineWidth, outlineHeight);

    int roomSize = size / mazeSize;
    int roomWidth = roomSize * 5 / 3, roomHeight = roomSize;

    int charLocations[4][2] = {{0, 0}, {0, 1}, {2, 0}, {2, 1}};

    for (int i = 0; i < mazeSize; i++) {
        for (int j = 0; j < mazeSize; j++) {
            MazeRoom* room = maze->getRoom(i, j);
            int boxX = x + i * roomWidth + 1;
            int boxY = y + j * roomHeight + 1;

            // If room not edge, draw line
            if (i != 0 && j != 0) {
                drawText("+", boxX, boxY, DIM);
            }

            if (dynamic_cast<MazeWall*>(room) != nullptr) {
                drawBox(boxX, boxY, roomWidth, roomHeight);
            }

            bool isStudent = false;
            if (MazeOpenSpace* peopleRoom = dynamic_cast<MazeOpenSpace*>(room)) {
                for (int k = 0; k < peopleRoom->getPeople().size(); k++) {
                    MazePerson* person = peopleRoom->getPeople()[k];
                    int charX = boxX + (roomWidth - 2) / 2;
                    int charY = boxY + (roomHeight - 2) / 2 + 1;  // +1 because emojis take up 2 width and only 1 height

                    drawText(person->getDisplayChar(), charX + charLocations[k][0], charY + charLocations[k][1]);
                    if (dynamic_cast<Student*>(person) != nullptr) {
                        isStudent = true;
                    }
                }
                if (isStudent) {
                    drawBox(boxX, boxY, roomWidth, roomHeight, CYAN);
                }
            }
        }
    }
}

void MazeElement::arrowKeyEvent(ArrowKey key, WindowElement* element) {
    Game::getInstance()->moveStudent(key);
}