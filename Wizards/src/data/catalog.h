#ifndef CATALOG_H
#define CATALOG_H

#include <string>
#include "spellbook.h"
#include "wizard.h"
#include <tuple>

using namespace std;

// Comments are in the CPP file
tuple<Spellbook*, int> searchSpellbook(Spellbook*, int, string);
tuple<Spellbook*, int> searchSpellbooksNumber(Spellbook*, int, int);
tuple<Spellbook*, int> searchSpellbooksEffect(Spellbook*, int, string);
tuple<Spellbook*, int> sortSpellbooks(Spellbook*, int);
void printToFile(string, Spellbook*, int, Wizard*);
void deleteInfo(Wizard**, Spellbook**, int);

#endif