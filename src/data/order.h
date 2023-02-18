#ifndef ORDER_H
#define ORDER_H

#include <string>

using namespace std;

class Order {
   public:
    // need to include accessor functions and mutator functions for private member when appropriate
    // need to include constructors and destructors where appropriate
    // need to use 'const' when appropriate
    Order();
    Order(int id, string coffee_name, char coffee_size, int quantity, bool orderFilled);
    Order(const Order& order);
    ~Order();

    int getId() const;
    string getCoffeeName() const;
    char getCoffeeSize() const;
    int getQuantity() const;

    void setCoffeeName(string coffee_name);
    void setCoffeeSize(char coffee_size);
    void setQuantity(int quantity);
    void setOrderFilled(bool orderFilled);

   private:
    int id;
    string coffeeName;
    char coffeeSize;
    int quantity;
    bool orderFilled;
};
#endif