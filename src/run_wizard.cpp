/*********************************************************************
** Program Filename: run_wizard.cpp
** Author: Aidan Schmitigal
** Date: 2/1/2023
** Description: A Spellbook Sorting and Searching Program for users of Pogwards
** Input: Spellbook and Wizard files
** Output: A program that allows users to search and sort spellbooks
*********************************************************************/

#include <iostream>
#include <unistd.h>
#include "graphics/window.h"
#include "graphics/text.h"
#include "graphics/textinput.h"
#include "graphics/util.h"
#include "graphics/button.h"
#include "graphics/lock.h"
#include "graphics/spellbookelement.h"
#include "graphics/userwelcome.h"
#include <fcntl.h>
#include <termios.h>
#include <tuple>
#include <fstream>
#include "data/spellbook.h"
#include "data/wizard.h"
#include "data/spell.h"
#include "data/catalog.h"

using namespace std;

void getInputFiles(Window* fileInputWindow, ifstream* spellbookFile, ifstream* wizardsFile);
void loadLibrary(Window* libraryWindow, Spellbook*& spellbooks, Wizard*& wizards, ifstream& spellbookFile, ifstream& wizardsFile, int numberOfSpellbooks, int numberOfWizards);
void login(Window* loginWindow, Wizard*& user, Wizard*& wizards, int numberOfWizards);
void showLibrary(Window* libraryWindow, Wizard*& user, Spellbook* spellbooks, int numberOfSpellbooks, int hiddenSpellbooks, bool showSpells = false);
void showActions(Window* libraryActionsWindow, Window* libraryWindow, Wizard*& user, Spellbook*& spellbooks, int numberOfSpellbooks);

int main() {
  Window::prepareScreen();

  ifstream spellbookFile;
  ifstream wizardsFile;

  Spellbook* spellbooks;
  int numberOfSpellbooks;
  Wizard* wizards;
  int numberOfWizards;
  
  Wizard* user = NULL;

  Window* fileInputWindow = new Window(1, "File Input");
  Window* loginWindow = new Window(1, "Login", true);
  Window* libraryActionsWindow = new Window(1, "Library Actions", true);
  Window* libraryWindow = new Window(2, "Library", true);

  getInputFiles(fileInputWindow, &spellbookFile, &wizardsFile);
  fileInputWindow->setHidden(true);
  loginWindow->setHidden(false);
  libraryWindow->setHidden(false);

  spellbookFile >> numberOfSpellbooks;
  wizardsFile >> numberOfWizards;

  loadLibrary(libraryWindow, spellbooks, wizards, spellbookFile, wizardsFile, numberOfSpellbooks, numberOfWizards);
  login(loginWindow, user, wizards, numberOfWizards);

  if (user != NULL) {
    showLibrary(libraryWindow, user, spellbooks, numberOfSpellbooks, 0);

    loginWindow->setHidden(true);
    libraryActionsWindow->setHidden(false);
    showActions(libraryActionsWindow, libraryWindow, user, spellbooks, numberOfSpellbooks);
  }

  // Delete all variable to free up memory
  // delete user;
  deleteInfo(&wizards, &spellbooks, numberOfSpellbooks);
  
  Window::exit();
  return 0;
}

/*********************************************************************
** Function: getInputFiles
** Description: Gets the input files from the user
** Parameters: Window* fileInputWindow, ifstream* spellbookFile, ifstream* wizardsFile
** Pre-Conditions: Window exits and is not hidden
** Post-Conditions: Files are opened
** Length Reasoning: Requires window management and file management
*********************************************************************/
void getInputFiles(Window* fileInputWindow, ifstream* spellbookFile, ifstream* wizardsFile) {
  // ~~~~~~~~~~~~~~~~~~~~~~ Set Up Window Input ~~~~~~~~~~~~~~~~~~~~~~~~~~
  TextInput* wizardsInput = new TextInput("Wizards File Name", "wizards.txt");
  fileInputWindow->addElement(wizardsInput, 1);
  TextInput* spellbookInput = new TextInput("Spellbook File Name", "spellbooks.txt");
  fileInputWindow->addElement(spellbookInput, 1);
  Button* submitButton = new Button("Submit");
  fileInputWindow->addElement(submitButton);

  /* ~~~~~~~~~~~~~~~~~~~~~~ Get Input ~~~~~~~~~~~~~~~~~~~~~~~~~~
  * This loop will run until the user enters a valid file name
  * for both the wizards and spellbooks files
  */
  do {
    string inputText = wizardsInput->getInput();
    wizardsFile->open(inputText);

    if (!wizardsFile->is_open()) {
      wizardsFile->open(inputText + ".txt");
      if (!wizardsFile->is_open()) {
        wizardsInput->setState(ERROR); // Sets the input box to ERORR state
        wizardsInput->setText("No file found.");
      }
    }

    if (wizardsFile->is_open()) {
      wizardsInput->setState(SUCCESS);
    }
  } while (!wizardsFile->is_open());
  wizardsInput->setState(SUCCESS);

  do {
    string inputText = spellbookInput->getInput();
    spellbookFile->open(inputText);

    if (!spellbookFile->is_open()) {
      spellbookFile->open(inputText + ".txt");
      if (!spellbookFile->is_open()) {
        spellbookInput->setState(ERROR); // Sets the input box to ERORR state
        spellbookInput->setText("No file found.");
      }
    }

    if (spellbookFile->is_open()) {
      spellbookInput->setState(SUCCESS);
    }
  } while (!spellbookFile->is_open());
  spellbookInput->setState(SUCCESS);
  
  submitButton->click();
  submitButton->setState(SUCCESS);
}

/*********************************************************************
** Function: loadLibrary
** Description: Parses the input files and creates the arrays
** Parameters: Window* libraryWindow, Spellbook*& spellbooks, Wizard*& wizards, ifstream& spellbookFile, ifstream& wizardsFile, int numberOfSpellbooks, int numberOfWizards
** Pre-Conditions: Files are opened
** Post-Conditions: Arrays are created and filled
*********************************************************************/
void loadLibrary(Window* libraryWindow, Spellbook*& spellbooks, Wizard*& wizards, ifstream& spellbookFile, ifstream& wizardsFile, int numberOfSpellbooks, int numberOfWizards) {
  Lock* lock = new Lock();
  lock->setLockedMessage("Please Login to Access the Library");
  libraryWindow->addElement(lock);

  // Creates and populates the spellbooks array
  spellbooks = createSpellbooks(numberOfSpellbooks);
  populateSpellbookData(spellbooks, numberOfSpellbooks, spellbookFile);

  // I didn't see a requirement for createWizards, so I just did it in the main function
  wizards = new Wizard[numberOfWizards];
  for (int i = 0; i < numberOfWizards; i++) {
    wizardsFile >> wizards[i].name >> wizards[i].id >> wizards[i].password >> wizards[i].positionTitle >> wizards[i].beardLength;
  }
}

/*********************************************************************
** Function: login
** Description: Prpts the user for a username and password
** Parameters: Window* loginWindow, Wizard*& user, Wizard*& wizards, int numberOfWizards
** Pre-Conditions: Arrays are created and filled
** Post-Conditions: User is logged in or program exits
** Length Reasoning: Requires window management and file management
*********************************************************************/
void login(Window* loginWindow, Wizard*& user, Wizard*& wizards, int numberOfWizards) {
  // ~~~~~~~~~~~~~~~~~~~~~~ Set Up Window Input ~~~~~~~~~~~~~~~~~~~~~~~~~~
  TextInput* usernameInput = new TextInput("Username", "123");
  loginWindow->addElement(usernameInput, 1);
  TextInput* passwordInput = new TextInput("Password", "********");
  loginWindow->addElement(passwordInput, 1);
  Button* submitButton = new Button("Submit");
  loginWindow->addElement(submitButton, 1);
  Text* triesLeftText = new Text("Attempts Remaining: 3");
  loginWindow->addElement(triesLeftText);

  /* ~~~~~~~~~~~~~~~~~~~~~~ Get Input ~~~~~~~~~~~~~~~~~~~~~~~~~~
  * This loop will run until the user enters a valid username and password
  * or they run out of attempts
  * Self explanatory when invalid username or password is entered + attempts remaining
  */

  int triesRemaining = 3; // Number of attempts remaining
  do {
    int usernameText = atoi(usernameInput->getInput().c_str());
    usernameInput->setState(DEFUALT);
    
    string passwordText = passwordInput->getInput();
    passwordInput->setState(DEFUALT);
    
    submitButton->click();
    
    for (int i = 0; i < numberOfWizards; i++) { 
      if (usernameText == wizards[i].id && passwordText == wizards[i].password) { // Checks if the username and password are valid
        usernameInput->setState(SUCCESS);
        passwordInput->setState(SUCCESS);
        submitButton->setState(SUCCESS);
        user = &wizards[i];
        break;
      }
    }
    if (user == NULL) { // If the username and password are invalid
      usernameInput->setState(ERROR);
      passwordInput->setState(ERROR);
      submitButton->setState(ERROR);
      triesRemaining--;
      triesLeftText->setText("Attempts Remaining: " + to_string(triesRemaining));
    }
  } while (user == NULL && triesRemaining != 0); // Loop will run until the user is logged in or they run out of attempts

  if (triesRemaining == 0 && user == NULL) { // If the user runs out of attempts
    triesLeftText->setText("You have run out of attempts.");
    cout << "You have run out of attempts." << endl;
  }
}

/*********************************************************************
** Function: showLibrary
** Description: Displays the library / changes the spellbooks in the library
** Parameters: Window* libraryWindow, Wizard*& user, Spellbook*& spellbooks, int numberOfSpellbooks, int hiddenSpellbooks
** Pre-Conditions: User is logged in
** Post-Conditions: Library is displayed
*********************************************************************/
void showLibrary(Window* libraryWindow, Wizard*& user, Spellbook* spellbooks, int numberOfSpellbooks, int hiddenSpellbooks, bool showSpells) {
  libraryWindow->removeAllElements();

  // This is the number that has been filtered out not what students can't see
  Text* hiddenSpellbooksText = new Text(to_string(hiddenSpellbooks) + " Hidden Spellbooks", 0);
  libraryWindow->addElement(hiddenSpellbooksText);
  hiddenSpellbooksText->setState(DISABLED);

  for (int i = 0; i < numberOfSpellbooks; i++) {
    bool hasDeathOrPoison = false;
    if (user->positionTitle == "Student") {
      for (int j = 0; j < spellbooks[i].numSpells; j++) {
        if (spellbooks[i].spells[j].effect == "death" || spellbooks[i].spells[j].effect == "poison") {
          hasDeathOrPoison = true;
        }
      }
    }
    if (!hasDeathOrPoison) {
      libraryWindow->addElement(new SpellbookElement(spellbooks[i], showSpells), 1);
    }
  }
}

/*********************************************************************
** Function: showActions
** Description: Displays the actions the user can take
** Parameters: Window* actionsWindow, Window* libraryWindow, Wizard*& user, Spellbook*& spellbooks, int numberOfSpellbooks
** Pre-Conditions: User is logged in
** Post-Conditions: Actions are displayed
** Length Reasoning: Requires window management and switch statements are long
*********************************************************************/
void showActions(Window* actionsWindow, Window* libraryWindow, Wizard*& user, Spellbook*& spellbooks, int numberOfSpellbooks) {
  // ~~~~~~~~~~~~~~~~~~~~~~ Set Up Window Input ~~~~~~~~~~~~~~~~~~~~~~~~~~
  UserWelcome* userWelcome = new UserWelcome(*user);
  actionsWindow->addElement(userWelcome, 1);

  Text* actionText = new Text("What would you like to do?\n1. Search Spellbooks\n2. Search Spellbooks by # Pages\n3. Search Spellbooks by Effect\n4. Sort Spellbooks\n5. Quit", 0.8);
  actionsWindow->addElement(actionText, 1);

  TextInput* actionInput = new TextInput("Action", "1-5");
  actionsWindow->addElement(actionInput, 1);

  TextInput* searchInput = new TextInput("Search", "Bubble");
  searchInput->setState(DISABLED);
  actionsWindow->addElement(searchInput);

  Button* submitButton = new Button("Submit");
  actionsWindow->addElement(submitButton);

  /* ~~~~~~~~~~~~~~~~~~~~~~ Get Input ~~~~~~~~~~~~~~~~~~~~~~~~~~
  * This loop will run until the user enters a valid action
  * Then handled the action
  * Then asks for printing the spellbooks
  */

  do {
    actionInput->setText("");
    searchInput->setState(DISABLED);

    int action = atoi((actionInput->getInput()).c_str());
    actionInput->setState(DEFUALT);

    string searchInputText;
    // Using a tuple to return two values
    // If we couldn't use tuples, I could use a struct
    tuple<Spellbook*, int> sortedSpellbooks;

    switch (action) { // Sets up the search input
      case 1:
      case 2:
      case 3:
        searchInput->setText("");
        searchInput->setState(DEFUALT);
        searchInputText = searchInput->getInput();
        submitButton->setTitle("Search");
        break;
      case 4:
        submitButton->setTitle("Sort");
        break;
      case 5:
        submitButton->setTitle("Quit");
        break;
    }

    submitButton->click();

    /* ~~~~~~~~~~~~~~~~~~~~~~ Handle Input ~~~~~~~~~~~~~~~~~~~~~~~~~~
    * This switch statement handles the action
    * Then asks for printing the spellbooks
    * Spellbooks are always displayed in the library window
    */

    switch (action) {
      case 1:
        //src/data/catalog.cpp
        sortedSpellbooks = searchSpellbook(spellbooks, numberOfSpellbooks, searchInputText);
        showLibrary(libraryWindow, user, get<0>(sortedSpellbooks), get<1>(sortedSpellbooks), numberOfSpellbooks - get<1>(sortedSpellbooks));
        break;
      case 2:
        //src/data/catalog.cpp
        sortedSpellbooks = searchSpellbooksNumber(spellbooks, numberOfSpellbooks, atoi(searchInputText.c_str()));
        showLibrary(libraryWindow, user, get<0>(sortedSpellbooks), get<1>(sortedSpellbooks), numberOfSpellbooks - get<1>(sortedSpellbooks));
        break;
      case 3:
        //src/data/catalog.cpp
        sortedSpellbooks = searchSpellbooksEffect(spellbooks, numberOfSpellbooks, searchInputText);
        showLibrary(libraryWindow, user, get<0>(sortedSpellbooks), get<1>(sortedSpellbooks), numberOfSpellbooks - get<1>(sortedSpellbooks), true);
        break;
      case 4:
        //src/data/catalog.cpp
        sortedSpellbooks = sortSpellbooks(spellbooks, numberOfSpellbooks);
        showLibrary(libraryWindow, user, get<0>(sortedSpellbooks), get<1>(sortedSpellbooks), numberOfSpellbooks - get<1>(sortedSpellbooks));
        break;
      case 5:
        //Exit
        return;
        break;
      default:
        actionInput->setState(ERROR);
        actionInput->setText("Invalid Action");
        continue;
        break;
    }

    /* ~~~~~~~~~~~~~~~~~~~~~~ Print to File ~~~~~~~~~~~~~~~~~~~~~~~~~~
    * Not asking for printing to screen because it is always displayed
    * 
    * This asks the user if they want to print the spellbooks to a file
    * If they input a file name, it will print the spellbooks to the file
    * Otherwise, it will not print the spellbooks to a file
    */
    if (get<1>(sortedSpellbooks) != 0) {
      TextInput* printButton = new TextInput("Enter a File Name", "Leave blank for no output.", 0.4);
      libraryWindow->addElement(printButton);

      string printFilename = printButton->getInput();
      libraryWindow->removeElement(printButton);

      if (printFilename.length() > 0) {
        printToFile(printFilename, get<0>(sortedSpellbooks), get<1>(sortedSpellbooks), user);
      }
    }

    delete[] get<0>(sortedSpellbooks);

  } while (true); // This loop will run until the user enters a valid action or quits
}