#ifndef COFFEE_H
#define COFFEE_H

#include <fstream>
#include <string>

using namespace std;

class Coffee {
   public:
    Coffee();
    Coffee(string name, float smallCost, float mediumCost, float largeCost, int smallSales, int mediumSales, int largeSales);
    Coffee& operator=(const Coffee& coffee);

    string getName() const;
    float getSmallCost() const;
    float getMediumCost() const;
    float getLargeCost() const;

    void setName(string name);
    void setSmallCost(float smallCost);
    void setMediumCost(float mediumCost);
    void setLargeCost(float largeCost);

    void addSmallSale();
    void addMediumSale();
    void addLargeSale();

   private:
    string name;
    int smallSales, mediumSales, largeSales;
    float smallCost, mediumCost, largeCost;
};

#endif