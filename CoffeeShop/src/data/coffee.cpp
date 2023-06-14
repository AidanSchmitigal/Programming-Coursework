#include "coffee.h"

using namespace std;

Coffee::Coffee() {
    name = "Empty Coffee";
    smallCost = 0.0;
    mediumCost = 0.0;
    largeCost = 0.0;
    smallSales = 0;
    mediumSales = 0;
    largeSales = 0;
}

Coffee::Coffee(string name, float smallCost, float mediumCost, float largeCost, int smallSales, int mediumSales, int largeSales) {
    this->name = name;
    this->smallCost = smallCost;
    this->mediumCost = mediumCost;
    this->largeCost = largeCost;
    this->smallSales = smallSales;
    this->mediumSales = mediumSales;
    this->largeSales = largeSales;
}

Coffee& Coffee::operator=(const Coffee& coffee) {
    this->name = coffee.name;
    this->smallCost = coffee.smallCost;
    this->mediumCost = coffee.mediumCost;
    this->largeCost = coffee.largeCost;
    this->smallSales = coffee.smallSales;
    this->mediumSales = coffee.mediumSales;
    this->largeSales = coffee.largeSales;

    return *this;
}

bool Coffee::operator==(const Coffee& coffee) {
    return this->name == coffee.name &&
           this->smallCost == coffee.smallCost &&
           this->mediumCost == coffee.mediumCost &&
           this->largeCost == coffee.largeCost &&
           this->smallSales == coffee.smallSales &&
           this->mediumSales == coffee.mediumSales &&
           this->largeSales == coffee.largeSales;
}

string Coffee::getName() const {
    return name;
}
float Coffee::getSmallCost() const {
    return smallCost;
}
float Coffee::getMediumCost() const {
    return mediumCost;
}
float Coffee::getLargeCost() const {
    return largeCost;
}

float Coffee::getCost(char size) const {
    switch (size) {
        case 'S':
            return smallCost;
        case 'M':
            return mediumCost;
        case 'L':
            return largeCost;
        default:
            return 0.0;
    }
}

void Coffee::setName(string name) {
    this->name = name;
}
void Coffee::setSmallCost(float smallCost) {
    this->smallCost = smallCost;
}
void Coffee::setMediumCost(float mediumCost) {
    this->mediumCost = mediumCost;
}
void Coffee::setLargeCost(float largeCost) {
    this->largeCost = largeCost;
}

void Coffee::addSmallSale() {
    smallSales++;
}
void Coffee::addMediumSale() {
    mediumSales++;
}
void Coffee::addLargeSale() {
    largeSales++;
}

int Coffee::getSmallSales() const {
    return smallSales;
}
int Coffee::getMediumSales() const {
    return mediumSales;
}
int Coffee::getLargeSales() const {
    return largeSales;
}
double Coffee::getRevenue() const {
    return (smallSales * smallCost) + (mediumSales * mediumCost) + (largeSales * largeCost);
}