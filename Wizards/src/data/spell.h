#ifndef SPELL_H
#define SPELL_H

#include <string>

using namespace std;

struct Spell {
 string title;
 float successRate;
 string effect;
};

// Comments are in the CPP file
Spell* createSpells(int numberOfSpells);
void populateSpellData(Spell* spells, int numberOfSpells, ifstream& spellbookFile);

#endif