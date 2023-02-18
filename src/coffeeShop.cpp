/******************************************************
** Program: coffeeShop.cpp
** Author: Aidan Schmitigal
** Date: 02/10/2023
** Description: A coffee shop kiosk for customers and employees
** Input: User actions
** Output: Shop status
******************************************************/
#include <TerminalGraphics.h>

#include <iostream>

#include "data/shop.h"

using namespace std;

/**
 * Coffee Keiosk
 * - Employee can:
 * 1. View shop revenue
 * 2. View orders
 * 3. Add an item to coffee menu
 * 4. Remove an item from coffee menu
 * 5. View coffee menu
 * 6. View address
 * 7. View phone number
 * 8. Log out
 *
 * - Customer can:
 * 1. View coffee menu
 * 2. Search by price
 * 3. Search by coffee name
 * 4. Place an order
 * 5. View address
 * 6. View phone
 * 7. Log out
 * -
 */

int main() {
    Shop shop = Shop();
    shop.loadData();

    cout << "Welcome to the Coffee Shop!" << endl;
    cout << "1. Employee" << endl;
    cout << "2. Customer" << endl;
    cout << "3. Exit" << endl;

    bool isEmployee = false;

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            isEmployee = true;
            break;
        case 2:
            break;
        case 3:
            cout << "Exiting..." << endl;
            return 0;
    }

    if (isEmployee) {
        cout << "Welcome, employee!" << endl;
        cout << "1. View shop revenue" << endl;
        cout << "2. View orders" << endl;
        cout << "3. Add an item to coffee menu" << endl;
        cout << "4. Remove an item from coffee menu" << endl;
        cout << "5. View coffee menu" << endl;
        cout << "6. View address" << endl;
        cout << "7. View phone number" << endl;
        cout << "8. Log out" << endl;

        cin >> choice;
        string name;
        double smallCost;
        double mediumCost;
        double largeCost;
        Coffee* coffeee;

        switch (choice) {
            case 1:
                cout << "Shop revenue: $" << shop.getRevenue() << endl;
                break;
            case 2:
                cout << "Orders:" << endl;
                for (int i = 0; i < shop.getNumberOfOrders(); i++) {
                    cout << shop.getOrders()[i].getId() << " " << shop.getOrders()[i].getCoffeeName() << " " << shop.getOrders()[i].getCoffeeSize() << " " << shop.getOrders()[i].getQuantity() << endl;
                }
                break;
            case 3:
                cout << "Add an item to coffee menu" << endl;

                cout << "Name: ";
                cin >> name;
                cout << "Small cost: ";
                cin >> smallCost;
                cout << "Medium cost: ";
                cin >> mediumCost;
                cout << "Large cost: ";
                cin >> largeCost;

                coffeee = new Coffee(name, smallCost, mediumCost, largeCost, 0, 0, 0);
                shop.addToMenu(coffeee);
                break;
            case 4:
                cout << "Remove an item from coffee menu" << endl;
                cin >> choice;
                shop.removeFromMenu(choice);

                break;
            case 5:
                cout << "Coffee menu:" << endl;
                for (int i = 0; i < shop.getNumberOfCoffees(); i++) {
                    cout << shop.getMenu().getCoffees()[i].getName() << " " << shop.getMenu().getCoffees()[i].getSmallCost() << " " << shop.getMenu().getCoffees()[i].getMediumCost() << " " << shop.getMenu().getCoffees()[i].getLargeCost() << endl;
                }
                break;
            case 6:
                cout << "Address: " << shop.getAddress() << endl;
                break;
            case 7:
                cout << "Phone number: " << shop.getPhone() << endl;
                break;
            case 8:
                cout << "Logging out..." << endl;
                break;
        }
    } else {
        cout << "Welcome, customer!" << endl;
        cout << "1. View coffee menu" << endl;
        cout << "2. Search by price" << endl;
        cout << "3. Search by coffee name" << endl;
        cout << "4. Place an order" << endl;
        cout << "5. View address" << endl;
        cout << "6. View phone" << endl;
        cout << "7. Log out" << endl;

        cin >> choice;

        double price;
        string name;
        int quantity;
        char size;
        Coffee coffee;
        Menu menu;
        Order* order;

        switch (choice) {
            case 1:
                cout << "Coffee menu:" << endl;
                for (int i = 0; i < shop.getNumberOfCoffees(); i++) {
                    cout << shop.getMenu().getCoffees()[i].getName() << " " << shop.getMenu().getCoffees()[i].getSmallCost() << " " << shop.getMenu().getCoffees()[i].getMediumCost() << " " << shop.getMenu().getCoffees()[i].getLargeCost() << endl;
                }
                break;
            case 2:
                cout << "Search by price" << endl;
                cin >> price;

                menu = shop.searchByPrice(price);
                for (int i = 0; i < menu.getNumberOfCoffees(); i++) {
                    cout << menu.getCoffees()[i].getName() << " " << menu.getCoffees()[i].getSmallCost() << " " << menu.getCoffees()[i].getMediumCost() << " " << menu.getCoffees()[i].getLargeCost() << endl;
                }
                break;
            case 3:
                cout << "Search by coffee name" << endl;
                cin >> name;
                coffee = shop.searchByName(name);
                cout << coffee.getName() << " " << coffee.getSmallCost() << " " << coffee.getMediumCost() << " " << coffee.getLargeCost() << endl;
                break;
            case 4:
                cout << "Place an order" << endl;
                // Print menu then ask for number then size then quantity
                cout << "Coffee menu:" << endl;
                for (int i = 0; i < shop.getNumberOfCoffees(); i++) {
                    cout << shop.getMenu().getCoffees()[i].getName() << " " << shop.getMenu().getCoffees()[i].getSmallCost() << " " << shop.getMenu().getCoffees()[i].getMediumCost() << " " << shop.getMenu().getCoffees()[i].getLargeCost() << endl;
                }
                cout << "Number: ";
                cin >> choice;
                cout << "Size: ";
                cin >> size;
                cout << "Quantity: ";
                cin >> quantity;

                order = new Order(shop.getNumberOfOrders() + 1, shop.getMenu().getCoffees()[choice - 1].getName(), size, quantity, false);
                shop.placeOrder(order);
                break;
            case 5:
                cout << "Address: " << shop.getAddress() << endl;
                break;
            case 6:
                cout << "Phone number: " << shop.getPhone() << endl;
                break;
            case 7:
                cout << "Logging out..." << endl;
                break;
        }
    }

    shop.saveData();
    return 0;
}