/*********************************************************************
** Program Filename: driver.cpp
** Author: Aidan Schmitigal
** Date: 4/7/2023
** Description: A maze game where the player must find the exit
** Input: Movement and code
** Output: A maze game
*********************************************************************/
#include "TerminalGraphics.h"
#include "data/game.h"

using namespace std;

int main() {
    srand(time(NULL));
    Terminal terminal(new VerticalLayout());
    Game* game = Game::getInstance();
    game->switchToStartScreen();
    Terminal::checkInputs();

    delete game;
}