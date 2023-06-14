/******************************************************
** Program: coffeeShop.cpp
** Author: Aidan Schmitigal
** Date: 02/10/2023
** Description: A coffee shop kiosk for customers and employees
** Input: User actions
** Output: Shop status
******************************************************/
#include <TerminalGraphics.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "data/shop.h"

using namespace std;

Group* createMenuCoffee(Group* menu, Coffee coffee, bool employeeMode, bool bestSeller);
void enterEmployeeMode(Text* welcomeText, Group* menu);
void enterCustomerMode(Text* welcomeText, Group* menu);
void enterOrderScreen(Group* menu, Coffee coffee);
void enterAddCoffeeScreen(Group* menu);

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

    Button* viewOrdersButton = new Button("View Orders", [&menu]() {
        menu->removeAllElements();
        Order* orders = shop.getOrders();
        for (int i = 0; i < shop.getNumberOfOrders(); i++) {
            Group* orderGroup = new Group(new VerticalLayout(), "Order #" + to_string(orders[i].getId()));
            orderGroup->addElement(new Icon("src/images/coffee/" + to_string(rand() % 15 + 1) + ".txt", 8, 5), 1);
            orderGroup->addElement(new Text(orders[i].getCoffeeName()));
            orderGroup->addElement(new Text("Size: " + to_string(orders[i].getCoffeeSize())));
            orderGroup->addElement(new Text("Quantity: " + to_string(orders[i].getQuantity())));
            orderGroup->addElement(new Text((string) "Filled: " + (orders[i].getOrderFilled() ? "Yes" : "No")), 1);

            Order* order = &orders[i];
            orderGroup->addElement(
                new Button("Fill Order", [order]() {
                    shop.fulfillOrder(order->getId());
                }),
                1);

            menu->addElement(orderGroup);
        }
    });
    Text* welcomeText = new Text("Welcome to the Coffee Shop!\nAddress: " + shop.getAddress() + "\nPhone: " + shop.getPhoneNumber() + (employeeMode ? "\nRevenue: $" + to_string(shop.getRevenue()) : ""));
    Button* employeeCustomerButton = new Button("Employee", [&employeeMode, &employeeCustomerButton, menuSorting, &viewOrdersButton, &welcomeText, &menu]() {
        employeeMode = !employeeMode;
        if (employeeMode) {
            employeeCustomerButton->setTitle("Customer");
            Terminal::rootWindow->select();
            enterEmployeeMode(welcomeText, menu);
            menuSorting->addElement(viewOrdersButton);
        } else {
            employeeCustomerButton->setTitle("Employee");
            Terminal::rootWindow->select();
            enterCustomerMode(welcomeText, menu);
            menuSorting->removeElement(viewOrdersButton, false);
        }
    });

    header->addElement(new Icon("src/images/icon.txt", 7, 5), 10);
    header->addElement(welcomeText, 1);
    header->addElement(new Spacer(0.5f));
    header->addElement(employeeCustomerButton, 1);
    header->addElement(new Button("Exit", []() {
        Terminal::exitFlag = true;
    }));

    TextInput* searchName = new TextInput("Sort by Name", "Mocha", 0.3);
    TextInput* searchPrice = new TextInput("Sort by Price", "3.50", 0.3);
    searchName->setKeyAction([&menu, &employeeMode](string text) {
        menu->removeAllElements();
        Menu* shopMenu = shop.searchByName(text);
        for (int i = 0; i < shopMenu->getNumberOfCoffees(); i++) {
            menu->addElement(createMenuCoffee(menu, shopMenu->getCoffees()[i], employeeMode, false));
        }
    });
    searchPrice->setKeyAction([&menu, &employeeMode](string text) {
        menu->removeAllElements();
        string searchtext = text == "" ? "0" : text;
        float input = atof(searchtext.c_str());
        Menu* shopMenu = shop.searchByPrice(input);
        for (int i = 0; i < shopMenu->getNumberOfCoffees(); i++) {
            menu->addElement(createMenuCoffee(menu, shopMenu->getCoffees()[i], employeeMode, false));
        }
    });
    menuSorting->addElement(searchName, 2);
    menuSorting->addElement(searchPrice, 2);

    enterCustomerMode(welcomeText, menu);

    Terminal::checkInputs();

    shop.saveData();
    return 0;
}

Group* createMenuCoffee(Group* menu, Coffee coffee, bool employeeMode, bool bestSeller) {
    Group* group = new Group(new VerticalLayout(), coffee.getName());
    if (bestSeller) group->setBackgroundColor(Color::BOLD);

    srand(coffee.getName().length() + coffee.getSmallCost() + coffee.getMediumCost() + coffee.getLargeCost());
    if (bestSeller) {
        group->addElement(new Text("Best Seller!", 0.0), 1);
    } else {
        group->addElement(new Spacer(2));
    }
    group->addElement(new Text(coffee.getName()), 1);
    group->addElement(new Icon("src/images/coffee/" + to_string(rand() % 15 + 1) + ".txt", 8, 5), 1);
    group->addElement(new Text("Large:  $" + to_string(coffee.getLargeCost()).substr(0, 4)));
    group->addElement(new Text("Medium: $" + to_string(coffee.getMediumCost()).substr(0, 4)));
    group->addElement(new Text("Small:  $" + to_string(coffee.getSmallCost()).substr(0, 4)), 1);
    group->addElement(new Button("Order", 0.8, [menu, coffee]() {
        enterOrderScreen(menu, coffee);
    }));
    if (employeeMode && !bestSeller) {
        group->addElement(new Button("Remove", 0.8, [coffee, menu, group]() {
            shop.removeFromMenu(coffee);
            menu->select();
            menu->removeElement(group);
        }));
    }

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
    menu->addElement(new Button("Add to Menu", 0.8, [menu]() {
        enterAddCoffeeScreen(menu);
    }));
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
    // menu->parent->parent->setHidden(true);

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
    orderGroup->addElement(new Button("Add to Order", [orderGroup, menu, smallButton, mediumButton, largeButton, quantityInput, coffee]() {
        if (smallButton->state == State::DEFAULT && mediumButton->state == State::DEFAULT && largeButton->state == State::DEFAULT) {
            smallButton->setState(State::ERROR);
            mediumButton->setState(State::ERROR);
            largeButton->setState(State::ERROR);
            return;
        }
        if (stoi("0" + quantityInput->getText()) <= 0) {
            quantityInput->setState(State::ERROR);
            return;
        }
        char size = smallButton->state == State::SUCCESS    ? 'S'
                    : mediumButton->state == State::SUCCESS ? 'M'
                                                            : 'L';
        shop.placeOrder(new Order(shop.getNumberOfOrders() + 1, coffee.getName(), size, stoi("0" + quantityInput->getText()), false));
        shop.addRevenue(coffee.getCost(size) * stoi("0" + quantityInput->getText()));

        shop.addOrderCount(coffee, size);
        Terminal::rootWindow->select();
        Terminal::rootWindow->addElement(menu->parent);
        Terminal::rootWindow->removeElement(orderGroup);
    }));

    orderGroup->addElement(new Button("Back", [orderGroup, menu]() {
        Terminal::rootWindow->select();
        Terminal::rootWindow->addElement(menu->parent);
        Terminal::rootWindow->removeElement(orderGroup);
    }));
    Terminal::rootWindow->addElement(orderGroup);
    orderGroup->select();
}

void enterAddCoffeeScreen(Group* menu) {
    Terminal::rootWindow->removeElement(menu->parent, false);

    Group* addCoffeeGroup = new Group(new VerticalLayout(), "Add Coffee");
    addCoffeeGroup->addElement(new Text("Add Coffee to Menu"), 1);

    TextInput* nameInput = new TextInput("Name", "", 0.5);
    addCoffeeGroup->addElement(nameInput);

    Group* costGroup = new Group(new HorizontalLayout());
    costGroup->widthPercent = 0.5;
    costGroup->heightPercent = -1;
    costGroup->height = 5;

    TextInput* smallCostInput = new TextInput("Small", "", 0.3);
    TextInput* mediumCostInput = new TextInput("Medium", "", 0.3);
    TextInput* largeCostInput = new TextInput("Large", "", 0.3);

    costGroup->addElement(smallCostInput, 1);
    costGroup->addElement(mediumCostInput, 1);
    costGroup->addElement(largeCostInput);
    addCoffeeGroup->addElement(costGroup);

    addCoffeeGroup->addElement(new Button("Add", 0.3, [addCoffeeGroup, menu, nameInput, smallCostInput, mediumCostInput, largeCostInput]() {
        if (nameInput->getText().length() == 0) {
            nameInput->setState(State::ERROR);
            return;
        }
        if (stoi("0" + smallCostInput->getText()) <= 0) {
            smallCostInput->setState(State::ERROR);
            return;
        }
        if (stoi("0" + mediumCostInput->getText()) <= 0) {
            mediumCostInput->setState(State::ERROR);
            return;
        }
        if (stoi("0" + largeCostInput->getText()) <= 0) {
            largeCostInput->setState(State::ERROR);
            return;
        }
        shop.addToMenu(new Coffee(nameInput->getText(), stoi("0" + smallCostInput->getText()), stoi("0" + mediumCostInput->getText()), stoi("0" + largeCostInput->getText()), 0, 0, 0));
        Terminal::rootWindow->select();
        Terminal::rootWindow->addElement(menu->parent);
        Terminal::rootWindow->removeElement(addCoffeeGroup);
    }));

    addCoffeeGroup->addElement(new Button("Back", 0.3, [addCoffeeGroup, menu]() {
        Terminal::rootWindow->select();
        Terminal::rootWindow->addElement(menu->parent);
        Terminal::rootWindow->removeElement(addCoffeeGroup);
    }));
    Terminal::rootWindow->addElement(addCoffeeGroup);
    addCoffeeGroup->select();
}