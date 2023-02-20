#ifndef SHOP_H
#define SHOP_H

#include <fstream>
#include <string>

#include "menu.h"
#include "order.h"

using namespace std;

class Shop {
   public:
    const static string MENU_FILE;
    const static string ORDERS_FILE;
    const static string INFO_FILE;

    void loadData();  // Read files
    void saveData();  // Write files

    Menu getMenu() const;            // Return menu
    int getNumberOfCoffees() const;  // Return number of coffees
    Order* getOrders() const;        // View orders
    int getNumberOfOrders() const;   // Return number of orders

    string getAddress() const;      // Return address
    string getPhoneNumber() const;  // Return phone number
    float getRevenue() const;       // Return revenue

    Coffee* getBestSellers() const;           // Return best sellers
    Menu* searchByPrice(double price) const;  // Search menu by price
    Menu* searchByName(string name) const;    // Search menu by name

    void placeOrder(Order* order);        // Place order
    void addToMenu(Coffee* coffee);       // Add item to menu
    void removeFromMenu(int index);       // Remove item from menu
    void removeFromMenu(Coffee* coffee);  // Remove item from menu

   private:
    Menu menu;
    string phoneNumber;
    string address;
    float revenue;
    Order* orders;
    int numberOfOrders;
};

#endif