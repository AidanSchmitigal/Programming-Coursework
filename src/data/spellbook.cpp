#include <iostream>
#include <fstream>
#include "spellbook.h"
#include "spell.h"

using namespace std;

/*********************************************************************
 * Function: createSpellbooks
 * Description: Creates an array of spellbooks
 * Parameters: int numberOfSpellbooks
 * Pre-Conditions: numberOfSpellbooks is a valid integer >= 0
 * Post-Conditions: Returns an array of spellbooks
 ********************************************************************/
Spellbook* createSpellbooks(int numberOfSpellbooks) {
    Spellbook *spellbooks = new Spellbook[numberOfSpellbooks];
    return spellbooks;
}

/*********************************************************************
 * Function: populateSpellbookData
 * Description: Populates the spellbook data
 * Parameters: Spellbook* spellbooks, int numberOfSpellbooks, ifstream& spellbookFile
 * Pre-Conditions: spellbooks is a valid array of spellbooks, numberOfSpellbooks is a valid integer >= 0, spellbookFile is a valid file
 * Post-Conditions: Populates the spellbook data
 ********************************************************************/
void populateSpellbookData(Spellbook* spellbooks, int numberOfSpellbooks, ifstream& spellbookFile) {
    for (int i = 0; i < numberOfSpellbooks; i++) {
        spellbookFile >> spellbooks[i].title >> spellbooks[i].author >> spellbooks[i].numPages >> spellbooks[i].edition >> spellbooks[i].numSpells;
        spellbooks[i].spells = createSpells(spellbooks[i].numSpells);
        populateSpellData(spellbooks[i].spells, spellbooks[i].numSpells, spellbookFile);
        
        float sum = 0;
        for (int j = 0; j < spellbooks[i].numSpells; j++) {
            sum += spellbooks[i].spells[j].successRate;
        }
        spellbooks[i].avgSuccessRate = sum / spellbooks[i].numSpells;
    }
}