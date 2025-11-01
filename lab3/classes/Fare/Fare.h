#pragma once
#include <iostream>
#include <string>

using namespace std;

enum class FareClass { Economy, PremiumEconomy, Business, FirstClass };

class Fare {
public:
    Fare(const string& fareCode, double price, FareClass fareClass,
        const string& tax, const string& discounts);

    void setFareCode(const string& fareCode);
    void setPrice(double price);
    void setFareClass(FareClass fareClass);
    void setTax(const string& tax);
    void setDiscounts(const string& discounts);

    const string& getFareCode() const;
    double getPrice() const;
    FareClass getFareClass() const;
    const string& getTax() const;
    const string& getDiscounts() const;

    double calculateTotal(double taxRate) const;
    void applyDiscount(double percent);
    bool isRefundable() const;

private:
    string fareCode_;
    double price_;
    FareClass fareClass_;
    string tax_;
    string discounts_;
};
