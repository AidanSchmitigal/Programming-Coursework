#ifndef MENU_H
#define MENU_H

#include <fstream>
#include <string>

#include "coffee.h"

using namespace std;

class Menu {
   public:
    // need to include accessor functions and mutator functions for private member when appropriate
    // need to include constructors, copy constructors, assignment operator overload,
    // and destructors where appropriate
    // need to use 'const' when appropriate
    Menu();
    Menu(const Menu& menu);
    ~Menu();

    Menu& operator=(const Menu& menu);

    // Suggested functions:
    Coffee& searchCoffeeByName(string name);
    Menu& searchCoffeeByPrice(int upper_bound);
    void addToMenu(Coffee& coffee_to_add);
    void removeFromMenu(int index_of_coffee_on_menu);

    Coffee* getCoffees() const;
    int getNumberOfCoffees() const;

    // feel free to add more member functions
   private:
    int numberOfCoffees;
    Coffee* coffees;
};

#endif