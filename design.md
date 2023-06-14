# Wizards Spell Book - Design

## Understanding the Problem

- Create a Spellbook Sorting and Searching Program for users of Pogwards
- Read in lists of spells and users and parse them into arrays of structs
- Allow only certain users to access spells & spellbooks

## Devising a Plan

- Create a struct for Spells, Spellbooks, and Users
- Create a function to read in the spells and users
- Create a function to parse the spells and users
- Create a function to delete / clear the data

## Carrying Out the Plan

### Main
```c++
Ask for files
Read in files
Parse files
Ask for user
Check user
Ask for spellbook
Ask for Action

Once done Delete all data
```

### Structs
```c++
struct User
    string name
    int id
    string password
    string position title
    flaod beard length

struct Spellbook
    string title
    string author
    int num_pages
    int edition
    int num_spells
    float avg_success_rate
    struct Spell *s

struct Spell
    string name
    float success_rate
    string effect
```

### Functions
```c++
Spellbook* create_spellbooks(int)
    return New spell book

void populate_spellbook_data(Spellbook *, int, ifstream &)
    read in spellbook data
    add data to spellbook

Spell * create_spells(int)
    return New spell

void populate_spell_data(Spell *, int, ifstream &)
    read in spell data
    add data to spell

void delete_info(Wizard **, Spellbook **)
    delete all data in arrays
```

## Tests

- File Input test
    - Input: File Name
    - Output: If it exists read in the file otherwise:
        "This files doesn't exist please try again"

- Username Test
    - Input: User Name
    - Output: If user exists ask for password else ask for username again

- Password Test
    - Input: Password
    - Output: If password is correct ask for action else ask for password again but only 3 times

- Action Test
    - Input: Action
    - Output: If action is valid do action else ask for action again

- Seach Test
    - Input: Search
    - Output: Find the search results unless user doesn't have access to those spells