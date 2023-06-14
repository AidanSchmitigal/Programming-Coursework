#include "spell.h"
#include <iostream>
#include <fstream>

using namespace std;

/*********************************************************************
 * Function: createSpells
 * Description: Creates an array of spells
 * Parameters: int numberOfSpells
 * Pre-Conditions: numberOfSpells is a valid integer >= 0
 * Post-Conditions: Returns an array of spells
 * *******************************************************************/
Spell* createSpells(int numberOfSpells) {
    Spell *spells = new Spell[numberOfSpells];
    return spells;
}

/*********************************************************************
 * Function: populateSpellData
 * Description: Populates the spell data
 * Parameters: Spell* spells, int numberOfSpells, ifstream& spellbookFile
 * Pre-Conditions: spells is a valid array of spells, numberOfSpells is a valid integer >= 0, spellbookFile is a valid file
 * Post-Conditions: Populates the spell data
 * *******************************************************************/
void populateSpellData(Spell* spells, int numberOfSpells, ifstream& spellbookFile) {
    for (int i = 0; i < numberOfSpells; i++) {
        spellbookFile >> spells[i].title >> spells[i].successRate >> spells[i].effect;
    }
}