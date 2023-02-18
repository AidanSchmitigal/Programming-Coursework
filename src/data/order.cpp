#include "order.h"

using namespace std;

Order::Order() {
    id = -1;
    coffeeName = "Empty Order";
    coffeeSize = '-';
    quantity = 0;
    orderFilled = true;
}
Order::Order(int id, string coffee_name, char coffee_size, int quantity, bool orderFilled) {
    this->id = id;
    this->coffeeName = coffee_name;
    this->coffeeSize = coffee_size;
    this->quantity = quantity;
    this->orderFilled = orderFilled;
}
Order::Order(const Order& order) {
    this->id = order.id;
    this->coffeeName = order.coffeeName;
    this->coffeeSize = order.coffeeSize;
    this->quantity = order.quantity;
    this->orderFilled = order.orderFilled;
}
Order::~Order() {
    // Nothing to do here
}

int Order::getId() const {
    return id;
}

string Order::getCoffeeName() const {
    return coffeeName;
}

char Order::getCoffeeSize() const {
    return coffeeSize;
}

int Order::getQuantity() const {
    return quantity;
}

void Order::setCoffeeName(string coffee_name) {
    this->coffeeName = coffee_name;
}

void Order::setCoffeeSize(char coffee_size) {
    this->coffeeSize = coffee_size;
}

void Order::setQuantity(int quantity) {
    this->quantity = quantity;
}

void Order::setOrderFilled(bool orderFilled) {
    this->orderFilled = orderFilled;
}