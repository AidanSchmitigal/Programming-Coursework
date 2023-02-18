#include "shop.h"

#include <iostream>
#include <ostream>
#include <sstream>

using namespace std;

const string Shop::MENU_FILE = "menu.txt";
const string Shop::ORDERS_FILE = "orders.txt";
const string Shop::INFO_FILE = "shop_info.txt";

void Shop::loadData() {
    ifstream menuFile(MENU_FILE);
    ifstream ordersFile(ORDERS_FILE);
    ifstream infoFile(INFO_FILE);

    if (!menuFile.is_open()) {
        cout << "Error opening menu file" << endl;
        return;
    }

    if (!ordersFile.is_open()) {
        cout << "Error opening orders file" << endl;
        return;
    }

    if (!infoFile.is_open()) {
        cout << "Error opening info file" << endl;
        return;
    }

    int numberOfCoffees;
    menuFile >> numberOfCoffees;
    string currentLine;
    for (int i = 0; i < numberOfCoffees; i++) {
        getline(menuFile, currentLine);
        string name;
        float smallCost, mediumCost, largeCost;
        int smallSales = 0, mediumSales = 0, largeSales = 0;

        stringstream ss(currentLine);
        ss >> name >> smallCost >> mediumCost >> largeCost;
        ss >> smallSales >> mediumSales >> largeSales;

        Coffee coffee = Coffee(name, smallCost, mediumCost, largeCost, smallSales, mediumSales, largeSales);
        menu.addToMenu(coffee);
    }

    ordersFile >> numberOfOrders;
    orders = new Order[numberOfOrders];
    for (int i = 0; i < numberOfOrders; i++) {
        int orderNum;
        string name;
        char size;
        int quantity;
        bool orderFilled = false;

        ordersFile >> orderNum >> name >> size >> quantity;
        // if (ordersFile.peek() != '\n') {
        //     ordersFile >> orderFilled;
        // }

        orders[i] = Order(orderNum, name, size, quantity, orderFilled);
    }

    infoFile >> phoneNumber;
    infoFile >> address;
    infoFile >> revenue;

    if (infoFile.fail()) {
        revenue = 0;
    }

    menuFile.close();
    ordersFile.close();
    infoFile.close();
}

void Shop::saveData() {
    ofstream menuFile(MENU_FILE);
    ofstream ordersFile(ORDERS_FILE);
    ofstream infoFile(INFO_FILE);

    if (!menuFile.is_open()) {
        cout << "Error opening menu file" << endl;
        return;
    }

    if (!ordersFile.is_open()) {
        cout << "Error opening orders file" << endl;
        return;
    }

    if (!infoFile.is_open()) {
        cout << "Error opening info file" << endl;
        return;
    }

    menuFile << menu.getNumberOfCoffees() << endl;
    for (int i = 0; i < menu.getNumberOfCoffees(); i++) {
        menuFile << menu.getCoffees()[i].getName() << " "
                 << menu.getCoffees()[i].getSmallCost() << " "
                 << menu.getCoffees()[i].getMediumCost() << " "
                 << menu.getCoffees()[i].getLargeCost() << endl;
    }

    ordersFile << numberOfOrders << endl;
    for (int i = 0; i < numberOfOrders; i++) {
        ordersFile << orders[i].getId() << " "
                   << orders[i].getCoffeeName() << " "
                   << orders[i].getCoffeeSize() << " "
                   << orders[i].getQuantity() << endl;
    }

    infoFile << phoneNumber << endl;
    infoFile << address << endl;
    infoFile << revenue << endl;

    menuFile.close();
    ordersFile.close();
    infoFile.close();
}

string Shop::getAddress() const {
    return this->address;
}

string Shop::getPhone() const {
    return this->phoneNumber;
}

float Shop::getRevenue() const {
    return this->revenue;
}

Coffee& Shop::searchByName(string name) {
    return this->menu.searchCoffeeByName(name);
}

Menu& Shop::searchByPrice(double price) {
    return this->menu.searchCoffeeByPrice(price);
}

void Shop::placeOrder(Order* order) {
    Order* newOrders = new Order[numberOfOrders + 1];
    for (int i = 0; i < numberOfOrders; i++) {
        newOrders[i] = orders[i];
    }
    newOrders[numberOfOrders] = *order;
    delete[] orders;
    orders = newOrders;
    numberOfOrders++;
}

Menu Shop::getMenu() const {
    return this->menu;
}

int Shop::getNumberOfCoffees() const {
    return this->menu.getNumberOfCoffees();
}

Order* Shop::getOrders() const {
    return this->orders;
}

int Shop::getNumberOfOrders() const {
    return this->numberOfOrders;
}

void Shop::addToMenu(Coffee* coffee) {
    this->menu.addToMenu(*coffee);
}

void Shop::removeFromMenu(int index) {
    this->menu.removeFromMenu(index);
}

void Shop::removeFromMenu(Coffee* coffee) {
    for (int i = 0; i < menu.getNumberOfCoffees(); i++) {
        if (menu.getCoffees()[i].getName() == coffee->getName()) {
            menu.removeFromMenu(i);
            break;
        }
    }
}