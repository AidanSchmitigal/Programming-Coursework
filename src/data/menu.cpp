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

Menu* Menu::searchCoffeeByName(string name) const {
    Menu* menu = new Menu();
    for (int i = 0; i < numberOfCoffees; i++) {
        if (name == "" || coffees[i].getName().find(name) != string::npos) {
            menu->addToMenu(coffees[i]);
        }
    }
    return menu;
}
Menu* Menu::searchCoffeeByPrice(int upper_bound) const {
    Menu* menu = new Menu();
    for (int i = 0; i < numberOfCoffees; i++) {
        if (coffees[i].getSmallCost() <= upper_bound) {
            menu->addToMenu(coffees[i]);
        }
    }
    return menu;
}

Coffee* Menu::getBestSellers() const {
    Coffee* bestSellers = new Coffee[4];
    bestSellers[0] = coffees[0];

    for (int i = 1; i < numberOfCoffees; i++) {
        if (coffees[i].getSmallSales() > bestSellers[0].getSmallSales() || coffees[i].getMediumSales() > bestSellers[0].getMediumSales() || coffees[i].getLargeSales() > bestSellers[0].getLargeSales()) {
            bestSellers[0] = coffees[i];
        }
    }

    for (int i = 1; i < 4; i++) {
        bestSellers[i] = coffees[i];
        for (int j = i + 1; j < numberOfCoffees; j++) {
            if (coffees[j].getRevenue() > bestSellers[i].getRevenue()) {
                bestSellers[i] = coffees[j];
            }
        }
    }
    return bestSellers;
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