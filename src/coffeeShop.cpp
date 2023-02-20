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
#include <sstream>

#include "data/shop.h"

using namespace std;

/**
 * Coffee Keiosk
 * - Employee can:
 * 1. View shop revenue                 x v
 * 2. View orders                       x
 * 3. Add an item to coffee menu        x v
 * 4. Remove an item from coffee menu   x v
 * 5. View coffee menu                  x v d
 * 6. View address                      x v d
 * 7. View phone number                 x v
 * 8. Log out                           x v
 *
 * - Customer can:
 * 1. View coffee menu                  x v
 * 2. Search by price                   x v
 * 3. Search by coffee name             x v
 * 4. Place an order                    x v
 * 5. View address                      x v d
 * 6. View phone                        x v d
 * 7. Log out                           x v
 * -
 */

// Function declarations

Group* createMenuCoffee(Group* menu, Coffee coffee, bool employeeMode, bool bestSeller);
void enterEmployeeMode(Text* welcomeText, Group* menu);
void enterCustomerMode(Text* welcomeText, Group* menu);
void enterOrderScreen(Group* menu, Coffee coffee);

Shop shop = Shop();

int main() {
    shop.loadData();
    bool employeeMode = false;

    Terminal term(new RowLayout(new int[2]{1, 4}));
    Group* header = new Group(new HorizontalLayout());
    Group* menuGroup = new Group(new RowLayout(new int[2]{1, 4}));
    Group* menuSorting = new Group(new HorizontalLayout(), "Sorting");
    Group* menu = new Group(new ScrollingColumnsLayout(5), "Menu");
    menuGroup->addElement(menuSorting);
    menuGroup->addElement(menu);
    Terminal::rootWindow->addElement(header);
    Terminal::rootWindow->addElement(menuGroup);

    Text* welcomeText = new Text("Welcome to the Coffee Shop!\nAddress: " + shop.getAddress() + "\nPhone: " + shop.getPhoneNumber() + (employeeMode ? "\nRevenue: $" + to_string(shop.getRevenue()) : ""));
    Button* employeeCustomerButton = new Button("Employee", [&employeeMode, &employeeCustomerButton, &welcomeText, &menu]() {
        employeeMode = !employeeMode;
        if (employeeMode) {
            employeeCustomerButton->setTitle("Customer");
            enterEmployeeMode(welcomeText, menu);
        } else {
            employeeCustomerButton->setTitle("Employee");
            enterCustomerMode(welcomeText, menu);
        }
    });

    header->addElement(new Icon("src/images/icon.txt", 7, 5), 10);
    header->addElement(welcomeText, 1);
    header->addElement(new Spacer(0.5f));
    header->addElement(employeeCustomerButton, 1);
    header->addElement(new Button("Exit", []() {
        Terminal::exit();
    }));

    TextInput* searchName = new TextInput("Sort by Name", "Mocha", 0.3);
    TextInput* searchPrice = new TextInput("Sort by Price", "3.50", 0.3);
    searchName->setKeyAction([&menu, &searchName, &employeeMode](string text) {
        searchName->setTitle(text);
        menu->removeAllElements();
        Menu* shopMenu = shop.searchByName(text);
        for (int i = 0; i < shopMenu->getNumberOfCoffees(); i++) {
            menu->addElement(createMenuCoffee(menu, shopMenu->getCoffees()[i], employeeMode, false));
        }
    });
    searchPrice->setKeyAction([&menu, &searchPrice, &employeeMode](string text) {
        searchPrice->setTitle(text + to_string(rand()));
        menu->removeAllElements();
        text = "0" + text;
        cout << text << endl;
        Menu* shopMenu = shop.searchByPrice(stof(text));
        for (int i = 0; i < shopMenu->getNumberOfCoffees(); i++) {
            menu->addElement(createMenuCoffee(menu, shopMenu->getCoffees()[i], employeeMode, false));
        }
    });
    menuSorting->addElement(searchName, 2);
    menuSorting->addElement(searchPrice);

    enterCustomerMode(welcomeText, menu);

    Terminal::checkInputs();
    Terminal::exit();
    return 0;
}

Group* createMenuCoffee(Group* menu, Coffee coffee, bool employeeMode, bool bestSeller) {
    Group* group = new Group(new VerticalLayout(), coffee.getName());
    if (bestSeller) group->setBackgroundColor(Color::LIGHT_YELLOW);

    srand(coffee.getName().length());
    group->addElement(new Icon("src/images/coffee." + to_string(rand() % 5 + 1) + ".txt", 8, 5), 1);
    group->addElement(new Text("Large:  $" + to_string(coffee.getLargeCost()).substr(0, 4)));
    group->addElement(new Text("Medium: $" + to_string(coffee.getMediumCost()).substr(0, 4)));
    group->addElement(new Text("Small:  $" + to_string(coffee.getSmallCost()).substr(0, 4)), 1);
    group->addElement(new Button("Order", 0.8, [menu, coffee]() {
        enterOrderScreen(menu, coffee);
    }));
    if (employeeMode && !bestSeller) {
        group->addElement(new Button("Remove", 0.8, []() {
            // shop.removeFromMenu(i);
        }));
    }

    stringstream ss;
    ss << menu;
    menu->setTitle(ss.str());
    return group;
}

void enterEmployeeMode(Text* welcomeText, Group* menu) {
    welcomeText->setText("Welcome to the Coffee Shop!\nAddress: " + shop.getAddress() + "\nPhone: " + shop.getPhoneNumber() + "\nRevenue: $" + to_string(shop.getRevenue()));
    menu->removeAllElements();

    Coffee* bestSellers = shop.getBestSellers();
    for (int i = 0; i < 4; i++) {
        menu->addElement(createMenuCoffee(menu, bestSellers[i], true, true));
    }

    Coffee* shopMenu = shop.getMenu().getCoffees();
    for (int i = 0; i < shop.getNumberOfCoffees(); i++) {
        menu->addElement(createMenuCoffee(menu, shopMenu[i], true, false));
    }
}

void enterCustomerMode(Text* welcomeText, Group* menu) {
    welcomeText->setText("Welcome to the Coffee Shop!\nAddress: " + shop.getAddress() + "\nPhone: " + shop.getPhoneNumber());
    menu->removeAllElements();

    Coffee* bestSellers = shop.getBestSellers();
    for (int i = 0; i < 4; i++) {
        menu->addElement(createMenuCoffee(menu, bestSellers[i], false, true));
    }

    Coffee* shopMenu = shop.getMenu().getCoffees();
    for (int i = 0; i < shop.getNumberOfCoffees(); i++) {
        menu->addElement(createMenuCoffee(menu, shopMenu[i], false, false));
    }
}

void enterOrderScreen(Group* menu, Coffee coffee) {
    Terminal::rootWindow->removeElement(menu->parent, false);

    Group* orderGroup = new Group(new VerticalLayout(), "Order");
    orderGroup->addElement(new Text(coffee.getName()), 1);
    orderGroup->addElement(new Icon("src/images/coffee/1.txt", 8, 5));

    Group* sizeGroup = new Group(new HorizontalLayout());
    sizeGroup->widthPercent = 0.5;
    sizeGroup->heightPercent = -1;
    sizeGroup->height = 5;

    Button* smallButton = new Button("Small");
    Button* mediumButton = new Button("Medium");
    Button* largeButton = new Button("Large");

    smallButton->setAction([smallButton, mediumButton, largeButton]() {
        smallButton->setState(State::SUCCESS);
        mediumButton->setState(State::DEFAULT);
        largeButton->setState(State::DEFAULT);
    });
    mediumButton->setAction([smallButton, mediumButton, largeButton]() {
        smallButton->setState(State::DEFAULT);
        mediumButton->setState(State::SUCCESS);
        largeButton->setState(State::DEFAULT);
    });
    largeButton->setAction([smallButton, mediumButton, largeButton]() {
        smallButton->setState(State::DEFAULT);
        mediumButton->setState(State::DEFAULT);
        largeButton->setState(State::SUCCESS);
    });

    sizeGroup->addElement(smallButton);
    sizeGroup->addElement(mediumButton);
    sizeGroup->addElement(largeButton);
    orderGroup->addElement(sizeGroup);

    TextInput* quantityInput = new TextInput("Quantity", "1", 0.3);
    orderGroup->addElement(quantityInput);
    orderGroup->addElement(new Button("Add to Order", [orderGroup, menu, smallButton, mediumButton, quantityInput, coffee]() {
        Terminal::rootWindow->removeElement(orderGroup);
        Terminal::rootWindow->addElement(menu->parent);
        shop.placeOrder(new Order(coffee.getName(),
                                  smallButton->state == State::SUCCESS    ? 'S'
                                  : mediumButton->state == State::SUCCESS ? 'M'
                                                                          : 'L',
                                  stoi(quantityInput->getText()), false));
    }));

    orderGroup->addElement(new Button("Back", [orderGroup, menu]() {
        Terminal::rootWindow->removeElement(orderGroup);
        Terminal::rootWindow->addElement(menu->parent);
    }));
    Terminal::rootWindow->addElement(orderGroup);
    orderGroup->select();
}