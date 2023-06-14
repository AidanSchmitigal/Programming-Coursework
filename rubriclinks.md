User Inputs
- [Link](./src/run_wizard.cpp#L100) prompt the user for two file names: 1) wizards info, 2) spell info
- [Link](./src/run_wizard.cpp#L111) display error message and terminates gracefully if the user failed to provide existing file names

Wizard Login
- [Link](./src/run_wizard.cpp#L216) provide explanatory message when user supplies invalid credentials
- [Link](./src/run_wizard.cpp#L225) program terminates after 3 incorrect password attempts
- [Link](./src/run_wizard.cpp#L208) correct authentication functionality

Searching and Printing
- [Link](./src/run_wizard.cpp#L334) Program correctly searches and displays the spellbook by its name.
- [Link](./src/run_wizard.cpp#L339) Program correctly searches and displays the spellbooks if its pages is less or equal to the upper limit
- [Link](./src/run_wizard.cpp#L344) Program correctly searches and displays spells by effect (bubble, death, fire, memory_loss, poison)
- [Link](./src/run_wizard.cpp#L248) A student user never sees information on spells or spellbooks involving poison or death.

Other functionalities
- [Link](./src/run_wizard.cpp#L160) Use dynamic arrays of structs and correctly store information of both the wizards and the spellbooks.
- [Link](./src/run_wizard.cpp#L362) The user is able to request the output be redirected to a user-specified filename.
- [Link](./src/data/catalog.cpp#L92) The correct information is appended to that particular file.
- [Link](./src/run_wizard.cpp#L383) Program repeats until the user chooses to exit

Struct usage and Required functions
- Code defines/uses the [wizard](./src/data/wizard.h), [spellbook](./src/data/spellbook.h), and [spell](./src/data/spell.h) structs exactly as specified. (-5 pts for each incorrect struct, -10 pts at max)
Note: It's okay if the code uses additional structs for other purposes
- Use required function prototypes, -2 pts for each unmatched function:
- [Spellbook * create_spellbooks(int);](./src/data/spellbook.cpp#L8)
- [void populate_spellbook_data(Spellbook *, int, ifstream &);](./src/data/spellbook.cpp#L20)
- [Spell * create_spells(int);](./src/data/spell.cpp#L7)
- [void populate_spell_data(Spell *, int, ifstream &);](./src/data/spell.cpp#L19)
- [void delete_info (Wizard **, Spellbook **, int);](./src/data/catalog.cpp#L132)

File separation and zip
- Program was submitted as a single zip file
- Program was separated into a working [makefile](./Makefile), an [application.cpp](./src/run_wizard.cpp) file, a header .h file, and an implementation .cpp file (/src/data)

Program Style
- [Link](./src/run_wizard.cpp) Program header that contains author's name, description, etc
- [Link](./src/run_wizard.cpp) Function header for each function that contains function name, description, etc

- [Link](./src/data/catalog.cpp#L72) Program correctly sorts and displays spellbooks by the average success rate of the spells contained within in ascending order