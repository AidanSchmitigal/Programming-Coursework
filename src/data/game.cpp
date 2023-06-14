#include "game.h"

using namespace std;

Game* Game::instance = nullptr;

Game::Game() {
    size = 10;
    maze = new Maze(size);
    leaderboard = new Leaderboard();
}

Game::~Game() {
    delete maze;
    // delete instance;
}

Game* Game::getInstance() {
    if (instance == nullptr) {
        instance = new Game();
    }
    return instance;
}

void Game::setSize(int size) {
    this->size = size;
}

Maze* Game::getMaze() {
    return maze;
}

void Game::start(bool useAI) {
    delete maze;
    maze = new Maze(size, useAI);
    maze->generate();
}

void Game::moveStudent(ArrowKey direction) {
    // Moves student and return the first person in the same room
    bool studentInteracted = false;
    MazePerson* person = maze->moveStudent(direction);
    if (Skill* skill = dynamic_cast<Skill*>(person)) {
        Game::getInstance()->switchToBattleScreen(skill);
        studentInteracted = true;
    } else if (TA* ta = dynamic_cast<TA*>(person)) {
        Game::getInstance()->switchToBattleScreen(ta);
        studentInteracted = true;
    } else if (Instructor* instructor = dynamic_cast<Instructor*>(person)) {
        Game::getInstance()->switchToBattleScreen(instructor);
        studentInteracted = true;
    }

    TA* ta = maze->moveTAs();
    if (!studentInteracted && ta != nullptr) {
        Game::getInstance()->switchToBattleScreen(ta);
    }
}

void Game::addStudentSkill(Skill* skill) {
    maze->getStudent()->addSkill();
    if (skill != nullptr) {
        maze->removeSkill(skill);
    }
}

void Game::beatTA(TA* ta) {
    maze->removeTA(ta);
    delete currentProgram;
    currentProgram = NULL;
}

Program* Game::getProgram(int level) {
    if (currentProgram != NULL) {
        delete currentProgram;
    }
    if (level == 10) {
        currentProgram = new Program("src/assets/code/final.txt");
        return currentProgram;
    }
    currentProgram = new Program("src/assets/code/" + to_string(level) + "-" + to_string(rand() % 3 + 1) + ".txt");
    return currentProgram;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Graphics ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Game::switchToStartScreen() {
    Terminal::rootWindow->removeAllElements();
    Icon* titleIcon = new Icon("src/assets/icons/title.txt", 77, 9);
    TextInput* sizeInput = new TextInput("Enter the size of the maze:", "", 0.4);
    sizeInput->setHidden(true);
    sizeInput->setExitAction([sizeInput](string text) {
        try {
            int size = stoi(text);
            if (size < 4 || size > 50) {
                throw invalid_argument("Invalid size");
            }
            sizeInput->setState(State::SUCCESS);

            Game* game = Game::getInstance();

            game->setSize(size);
            game->start();
            game->switchToGameScreen();
        } catch (invalid_argument& e) {
            sizeInput->setState(State::ERROR);
        }
    });
    Button* startButton = new Button(
        "Start", 0.4, [sizeInput]() {
            sizeInput->setHidden(false);
        });

    Button* leaderboardButton = new Button("Leaderboard", 0.4, []() {
        Game::getInstance()->switchToLeaderboardScreen();
    });
    Button* useAIButton = new Button("Use AI", 0.4, []() {
        Game* game = Game::getInstance();

        game->setSize(10);
        game->start(true);
        game->switchToGameScreen();
    });
    Button* exitButton = new Button("Exit", 0.4, []() { Terminal::exitFlag = true; });

    Terminal::rootWindow->addElement(titleIcon, 2);
    Terminal::rootWindow->addElement(startButton);
    Terminal::rootWindow->addElement(sizeInput);
    Terminal::rootWindow->addElement(leaderboardButton);
    Terminal::rootWindow->addElement(useAIButton);
    Terminal::rootWindow->addElement(exitButton);
    Terminal::rootWindow->select();
}

void Game::switchToLeaderboardScreen() {
    Terminal::rootWindow->removeAllElements();
    Icon* titleIcon = new Icon("src/assets/icons/title.txt", 77, 9);
    vector<pair<string, int>> entries = leaderboard->getScores();
    Group* leaderboardGroup = new Group(new VerticalLayout(), "Leaderboard");
    leaderboardGroup->heightPercent = 0.8;
    leaderboardGroup->addElement(new Text("I have no time :("));
    for (pair<string, int> entry : entries) {
        leaderboardGroup->addElement(new Text(entry.first + ": " + to_string(entry.second)));
    }
    Button* backButton = new Button("Back", 0.4, []() { Game::getInstance()->switchToStartScreen(); });

    Terminal::rootWindow->addElement(titleIcon, 2);
    Terminal::rootWindow->addElement(leaderboardGroup);
    Terminal::rootWindow->addElement(backButton);

    Terminal::rootWindow->select();
}

void Game::switchToGameScreen() {
    Terminal::rootWindow->removeAllElements();
    Icon* titleIcon = new Icon("src/assets/icons/title.txt", 77, 9);

    Group* gameGroup = new Group(new HorizontalLayout(), "Game");
    MazeElement* mazeElement = new MazeElement();

    Group* gameInfoGroup = new Group(new VerticalLayout(), "Game Info");
    gameGroup->addElement(mazeElement);
    gameGroup->addElement(gameInfoGroup);

    Text* emojiKey = new Text("You: 🎒\nTA: 🎓\nSkill: 💾\nInstructor: 💻");
    Text* instructionsText = new Text("Use the arrow keys to move around the maze.");
    Icon* instructionsIcon = new Icon("src/assets/icons/arrowKeys.txt", 5, 3);
    Text* instructions2Text = new Text("Avoid the TAs and reach the instructor to win.");
    Text* scoreText = new Text("Programming Skills: " + to_string(maze->getStudent()->getSkill()));
    Text* taCountText = new Text("TAs Remaining: " + to_string(maze->getNumTAs()));

    gameInfoGroup->addElement(emojiKey, 1);
    gameInfoGroup->addElement(instructionsText, 1);
    gameInfoGroup->addElement(instructionsIcon, 1);
    gameInfoGroup->addElement(instructions2Text, 1);
    gameInfoGroup->addElement(scoreText, 1);
    gameInfoGroup->addElement(taCountText);

    Terminal::rootWindow->addElement(titleIcon);
    Terminal::rootWindow->addElement(gameGroup);
    Terminal::rootWindow->select();
}

void Game::switchToBattleScreen(Skill* skill) {
    Terminal::rootWindow->removeAllElements();

    Icon* titleIcon = new Icon("src/assets/icons/title.txt", 77, 9);
    Group* battleGroup = new Group(new ColumnLayout(new int[2]{3, 1}), "Battle");

    Group* manualGroup = new Group(new VerticalLayout(), "Manual");

    FilePreview* manualPreview = new FilePreview("src/assets/manuals/" + to_string(maze->getStudent()->getSkill() + 1) + ".txt");

    manualGroup->addElement(manualPreview);

    Group* rightGroup = new Group(new VerticalLayout(), "Skill");

    Icon* skillIcon = new Icon("src/assets/icons/skill.txt", 25, 6);
    Text* battleText = new Text("You have encountered a bit of Skill!");
    Button* exitButton = new Button("Return", 0.4, [skill]() {
        Game* game = Game::getInstance();
        game->addStudentSkill(skill);
        game->switchToGameScreen();
    });

    rightGroup->addElement(skillIcon);
    rightGroup->addElement(battleText);
    rightGroup->addElement(exitButton);

    battleGroup->addElement(manualGroup);
    battleGroup->addElement(rightGroup);

    Terminal::rootWindow->addElement(titleIcon);
    Terminal::rootWindow->addElement(battleGroup);

    Terminal::rootWindow->select();
}

void Game::switchToBattleScreen(TA* ta) {
    Terminal::rootWindow->removeAllElements();
    if (maze->getStudent()->getSkill() == 0) {
        switchToEndScreen(false, vector<string>(1, "You didn't even do the homework. :/"));
        return;
    }

    Icon* titleIcon = new Icon("src/assets/icons/title.txt", 77, 9);
    Group* battleGroup = new Group(new ColumnLayout(new int[2]{3, 1}), "Battle");

    Group* inputGroup = new Group(new VerticalLayout(), "Testing");

    Icon* taIcon = new Icon("src/assets/icons/ta/" + to_string(rand() % 3 + 1) + ".txt", 25, 6);

    Program* program = getProgram(maze->getStudent()->getSkill());

    Text* questionText = new Text(program->getQuestion());
    TextField* programInput = new TextField("Enter the program to test:", "");
    if (maze->usingAI()) programInput->setText(vector<string>(1, "cheat"));
    programInput->setHeader(program->getDisplayHeaderCode());
    programInput->setFooter(program->getDisplayFooterCode());

    programInput->setLineNumbers(true);

    inputGroup->addElement(taIcon, 5);
    inputGroup->addElement(questionText, 1);
    inputGroup->addElement(programInput, 1);

    Group* rightGroup = new Group(new VerticalLayout(), "TA Stats");

    Text* taStatsText = new Text("TA Stats");
    Button* testButton = new Button("Test", 0.4, [ta, program, programInput]() {
        vector<string> input = programInput->getText();
        tuple<int, vector<string>> exit = program->runCode(input);

        Game* game = Game::getInstance();
        if (get<0>(exit) == 0) {
            game->beatTA(ta);
            game->switchToGameScreen();
        } else {
            game->switchToEndScreen(false, get<1>(exit));
        }
    });

    rightGroup->addElement(taStatsText);
    rightGroup->addElement(testButton);

    battleGroup->addElement(inputGroup);
    battleGroup->addElement(rightGroup);

    Terminal::rootWindow->addElement(titleIcon);
    Terminal::rootWindow->addElement(battleGroup);

    Terminal::rootWindow->select();
}

void Game::switchToBattleScreen(Instructor* instructor) {
    Terminal::rootWindow->removeAllElements();
    if (maze->getStudent()->getSkill() < 6 && !maze->usingAI()) {
        switchToEndScreen(false, vector<string>(1, "Come on. You didn't even try to get the skill. :/"));
        return;
    }

    Icon* titleIcon = new Icon("src/assets/icons/title.txt", 77, 9);
    Group* battleGroup = new Group(new ColumnLayout(new int[2]{3, 1}), "Battle");

    Group* inputGroup = new Group(new VerticalLayout(), "Testing");
    Icon* taIcon = new Icon("src/assets/icons/instructor.txt", 27, 5);

    Program* program = getProgram(10);

    Text* questionText = new Text(program->getQuestion());
    TextField* programInput = new TextField("Enter the program to test:", "");
    if (maze->usingAI()) programInput->setText(vector<string>(1, "cheat"));
    programInput->setHeader(program->getDisplayHeaderCode());
    programInput->setFooter(program->getDisplayFooterCode());

    programInput->setLineNumbers(true);

    inputGroup->addElement(taIcon, 5);
    inputGroup->addElement(questionText, 1);
    inputGroup->addElement(programInput, 1);

    Group* rightGroup = new Group(new VerticalLayout(), "TA Stats");

    Text* taStatsText = new Text("TA Stats");
    Button* testButton = new Button("Test", 0.4, [instructor, program, programInput]() {
        vector<string> input = programInput->getText();
        tuple<int, vector<string>> exit = program->runCode(input);

        Game* game = Game::getInstance();
        game->switchToEndScreen(get<0>(exit) == 0, get<1>(exit));
    });

    rightGroup->addElement(taStatsText);
    rightGroup->addElement(testButton);

    battleGroup->addElement(inputGroup);
    battleGroup->addElement(rightGroup);

    Terminal::rootWindow->addElement(titleIcon);
    Terminal::rootWindow->addElement(battleGroup);

    Terminal::rootWindow->select();
}

void Game::switchToEndScreen(bool win, vector<string> text) {
    Terminal::rootWindow->removeAllElements();

    Icon* titleIcon = new Icon("src/assets/icons/title.txt", 77, 9);
    Terminal::rootWindow->addElement(titleIcon, 1);
    if (win) {
        Icon* winIcon = new Icon("src/assets/icons/win.txt", 77, 9);
        Terminal::rootWindow->addElement(winIcon);
    } else {
        Icon* loseIcon = new Icon("src/assets/icons/lose.txt", 77, 9);
        Text* loseText = new Text("Here is your code's error:");
        string loseTextString = "";
        for (string line : text) {
            loseTextString += line + "\n";
        }
        Text* loseCodeText = new Text(loseTextString);

        Terminal::rootWindow->addElement(loseIcon, 1);
        Terminal::rootWindow->addElement(loseText, 1);
        Terminal::rootWindow->addElement(loseCodeText);
    }

    Button* returnToMenu = new Button("Return to Menu", 0.4, []() {
        Game* game = Game::getInstance();
        game->switchToStartScreen();
    });
    Terminal::rootWindow->addElement(returnToMenu);

    Terminal::rootWindow->select();
}
