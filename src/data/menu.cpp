#include "menu.h"

using namespace std;

Menu::Menu() {
    numberOfCoffees = 0;
    coffees = new Coffee[numberOfCoffees];
}
Menu::Menu(const Menu& menu) {
    numberOfCoffees = menu.numberOfCoffees;
    coffees = new Coffee[numberOfCoffees];
    for (int i = 0; i < numberOfCoffees; i++) {
        coffees[i] = menu.coffees[i];
    }
}
Menu::~Menu() {
    delete[] coffees;
}

Menu& Menu::operator=(const Menu& menu) {
    numberOfCoffees = menu.numberOfCoffees;
    coffees = new Coffee[numberOfCoffees];
    for (int i = 0; i < numberOfCoffees; i++) {
        coffees[i] = menu.coffees[i];
    }

    return *this;
}

Coffee& Menu::searchCoffeeByName(string name) {
    for (int i = 0; i < numberOfCoffees; i++) {
        if (coffees[i].getName() == name) {
            return coffees[i];
        }
    }
    return coffees[0];
}
Menu& Menu::searchCoffeeByPrice(int upper_bound) {
    Menu* menu = new Menu();
    for (int i = 0; i < numberOfCoffees; i++) {
        if (coffees[i].getSmallCost() <= upper_bound) {
            menu->addToMenu(coffees[i]);
        }
    }
    return *menu;
}
void Menu::addToMenu(Coffee& coffee_to_add) {
    Coffee* temp = new Coffee[numberOfCoffees + 1];
    for (int i = 0; i < numberOfCoffees; i++) {
        temp[i] = coffees[i];
    }
    temp[numberOfCoffees] = coffee_to_add;
    numberOfCoffees++;
    delete[] coffees;
    coffees = temp;
}
void Menu::removeFromMenu(int index_of_coffee_on_menu) {
    Coffee* temp = new Coffee[numberOfCoffees - 1];
    for (int i = 0; i < index_of_coffee_on_menu; i++) {
        temp[i] = coffees[i];
    }
    for (int i = index_of_coffee_on_menu; i < numberOfCoffees - 1; i++) {
        temp[i] = coffees[i + 1];
    }
    numberOfCoffees--;
    delete[] coffees;
    coffees = temp;
}

Coffee* Menu::getCoffees() const {
    return coffees;
}
int Menu::getNumberOfCoffees() const {
    return numberOfCoffees;
}