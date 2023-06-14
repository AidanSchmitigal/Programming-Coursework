#ifndef SPELLBOOK_H
#define SPELLBOOK_H

#include <string>

using namespace std;

struct Spellbook {
  string title;
  string author;
  int numPages;
  int edition;
  int numSpells;
  float avgSuccessRate;
  struct Spell* spells;
};

// Comments are in the CPP file
Spellbook* createSpellbooks(int numberOfSpellbooks);
void populateSpellbookData(Spellbook* spellbooks, int numberOfSpellbooks, ifstream& spellbookFile);

#endif