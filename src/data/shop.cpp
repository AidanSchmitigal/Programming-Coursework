#include "shop.h"

#include <curl/curl.h>

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

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
    menuFile >> numberOfCoffees >> ws;
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

    ordersFile >> numberOfOrders >> ws;
    orders = new Order[numberOfOrders];
    for (int i = 0; i < numberOfOrders; i++) {
        getline(ordersFile, currentLine);
        int orderNum;
        string name;
        char size;
        int quantity;
        bool orderFilled = false;

        stringstream ss(currentLine);
        ss >> orderNum >> name >> size >> quantity;
        ss >> orderFilled;

        orders[i] = Order(orderNum, name, size, quantity, orderFilled);
    }

    getline(infoFile, phoneNumber);
    getline(infoFile, address);
    string revenueString;
    getline(infoFile, revenueString);

    if (infoFile.fail()) {
        revenue = 0;
    } else {
        revenue = stof(revenueString);
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
                 << menu.getCoffees()[i].getLargeCost() << " "
                 << menu.getCoffees()[i].getSmallSales() << " "
                 << menu.getCoffees()[i].getMediumSales() << " "
                 << menu.getCoffees()[i].getLargeSales() << endl;
    }

    ordersFile << numberOfOrders << endl;
    for (int i = 0; i < numberOfOrders; i++) {
        ordersFile << orders[i].getId() << " "
                   << orders[i].getCoffeeName() << " "
                   << orders[i].getCoffeeSize() << " "
                   << orders[i].getQuantity() << " "
                   << orders[i].getOrderFilled() << endl;
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

string Shop::getPhoneNumber() const {
    return this->phoneNumber;
}

float Shop::getRevenue() const {
    return this->revenue;
}

Menu* Shop::searchByName(string name) const {
    return this->menu.searchCoffeeByName(name);
}

Menu* Shop::searchByPrice(float price) const {
    return this->menu.searchCoffeeByPrice(price);
}
Coffee* Shop::getBestSellers() const {
    return this->menu.getBestSellers();
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

    postRequest("/addcoffee",
                "{\"name\": \"" + order->getCoffeeName() +
                    "\", \"size\": \"" + order->getCoffeeSize() +
                    "\", \"id\": " + to_string(order->getId()) +
                    ", \"fulfilled\": " + to_string(order->getOrderFilled()) +
                    ", \"quantity\":\"" + to_string(order->getQuantity()) + "\"}");
}

void Shop::fulfillOrder(int orderNum) {
    for (int i = 0; i < numberOfOrders; i++) {
        if (orders[i].getId() == orderNum) {
            orders[i].setOrderFilled(true);

            postRequest("/fulfillorder", "{\"id\": " + to_string(orders[i].getId()) + "}");
            break;
        }
    }
}

void Shop::addRevenue(float revenue) {
    this->revenue += revenue;
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

void Shop::removeFromMenu(Coffee coffee) {
    for (int i = 0; i < menu.getNumberOfCoffees(); i++) {
        if (menu.getCoffees()[i] == coffee) {
            menu.removeFromMenu(i);
            break;
        }
    }
}

void Shop::addOrderCount(Coffee coffee, char size) {
    for (int i = 0; i < menu.getNumberOfCoffees(); i++) {
        if (menu.getCoffees()[i] == coffee) {
            menu.addOrderCount(i, size);
        }
    }
}

void Shop::postRequest(string url, string data) {
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, ("http://localhost:3000" + url).c_str());
        // curl_easy_setopt(curl, CURLOPT_URL, ("https://aidan.schmitigal.com/coffees/" + url).c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
}