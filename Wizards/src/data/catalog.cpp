#include "catalog.h"
#include "spellbook.h"
#include "spell.h"
#include "wizard.h"
#include <iostream>
#include <string>
#include <fstream>
#include <tuple>

using namespace std;

/*********************************************************************
** Function: searchSpellbook
** Description: Searches for spellbooks with a given name
** Parameters: Spellbook* spellbooks, int size, string name
** Pre-Conditions: Spellbooks has been initialized
** Post-Conditions: Returns a tuple with the spellbooks and the number of spellbooks
*********************************************************************/ 
tuple<Spellbook*, int> searchSpellbook(Spellbook* spellbooks, int size, string name) {
  Spellbook* result = new Spellbook[size];
  int resultSize = 0;
  for (int i = 0; i < size; i++) {
    if (spellbooks[i].title == name) {
      result[resultSize] = spellbooks[i];
      resultSize++;
    }
  }
  return make_tuple(result, resultSize);
}

/*********************************************************************
** Function: searchSpellbooksNumber
** Description: Searches for spellbooks with a given number of pages or less
** Parameters: Spellbook* spellbooks, int size, int num_pages
** Pre-Conditions: Spellbooks has been initialized
** Post-Conditions: Returns a tuple with the spellbooks and the number of spellbooks
*********************************************************************/
tuple<Spellbook*, int> searchSpellbooksNumber(Spellbook* spellbooks, int size, int num_pages) {
  Spellbook* result = new Spellbook[size];
  int resultSize = 0;
  for (int i = 0; i < size; i++) {
    if (spellbooks[i].numPages <= num_pages) {
      result[resultSize] = spellbooks[i];
      resultSize++;
    }
  }
  return make_tuple(result, resultSize);
}

/*********************************************************************
 * Function: searchSpellbooksEffect
 * Description: Searches for spellbooks with a given effect
 * Parameters: Spellbook* spellbooks, int size, string effect
 * Pre-Conditions: Spellbooks has been initialized
 * Post-Conditions: Returns a tuple with the spellbooks and the number of spellbooks
 * *******************************************************************/
tuple<Spellbook*, int> searchSpellbooksEffect(Spellbook* spellbooks, int size, string effect) {
  Spellbook* result = new Spellbook[size];
  int resultSize = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < spellbooks[i].numSpells; j++) {
      if (spellbooks[i].spells[j].effect == effect) {
        result[resultSize] = spellbooks[i];
        resultSize++;
        break;
      }
    }
  }
  return make_tuple(result, resultSize);
}

/*********************************************************************
 * Function: sortSpellbooks
 * Description: Sorts the spellbooks with a given success rate or higher
 * Parameters: Spellbook* spellbooks, int size
 * Pre-Conditions: Spellbooks has been initialized
 * Post-Conditions: Returns a tuple with the spellbooks and the number of spellbooks
 * *******************************************************************/
tuple<Spellbook*, int> sortSpellbooks(Spellbook* spellbooks, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (spellbooks[j].avgSuccessRate > spellbooks[j + 1].avgSuccessRate) {
        Spellbook temp = spellbooks[j];
        spellbooks[j] = spellbooks[j + 1];
        spellbooks[j + 1] = temp;
      }
    }
  }
  return make_tuple(spellbooks, size);
}

/*********************************************************************
 * Function: printToFile
 * Description: Prints the spellbooks to a file
 * Parameters: string printFilename, Spellbook* spellbooks, int numberOfSpellbooks
 * Pre-Conditions: Spellbooks has been initialized
 * Post-Conditions: Prints the spellbooks to a file
 * *******************************************************************/
void printToFile(string printFilename, Spellbook* spellbooks, int numberOfSpellbooks, Wizard* user) {
  ofstream file;
  if (printFilename.length() <= 4 || printFilename.substr(printFilename.length() - 4) != ".txt") {
    printFilename += ".txt";
  }
  file.open(printFilename, ios::out | ios::app);
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
      file << "Title: " << spellbooks[i].title << endl;
      file << "├ Author: " << spellbooks[i].author << endl;
      file << "├ Number of pages: " << spellbooks[i].numPages << endl;
      file << "├ Edition: " << spellbooks[i].edition << endl;
      file << "├ Average success rate: " << spellbooks[i].avgSuccessRate << endl;
      for (int j = 0; j < spellbooks[i].numSpells; j++) {
        file << (j == spellbooks[i].numSpells - 1 ? "╰" : "├") << " Spell " << j + 1 << endl;
        file << (j == spellbooks[i].numSpells - 1 ? " " : "│") << " ├ Title: " << spellbooks[i].spells[j].title << endl;
        file << (j == spellbooks[i].numSpells - 1 ? " " : "│") << " ├ Effect: " << spellbooks[i].spells[j].effect << endl;
        file << (j == spellbooks[i].numSpells - 1 ? " " : "│") << " ╰ Success rate: " << spellbooks[i].spells[j].successRate << endl;
      }
      file << endl;
    }
  }
  file.close();
}

/*********************************************************************
 * Function: deleteInfo
 * Description: Deletes the spellbooks and wizards
 * Parameters: Wizard** wizards, Spellbook** spellbooks, int numberOfSpellbooks
 * Pre-Conditions: Spellbooks and Wizards has been initialized
 * Post-Conditions: Deletes the spellbooks and wizards
 * *******************************************************************/
void deleteInfo(Wizard** wizards, Spellbook** spellbooks, int numberOfSpellbooks) {
  for (int i = 0; i < numberOfSpellbooks; i++) {
    delete[] (*spellbooks)[i].spells;
  }
  delete[] *spellbooks;
  delete[] *wizards;
}