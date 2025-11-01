#include "Fare.h"

Fare::Fare(const string& fareCode, double price, FareClass fareClass,
    const string& tax, const string& discounts) : 
    fareCode_(fareCode),
    price_(price),
    fareClass_(fareClass),
    tax_(tax),
    discounts_(discounts) {
}

void Fare::setFareCode(const string& fareCode) { 
    fareCode_ = fareCode; 
}
void Fare::setPrice(double price) {
    price_ = price; 
}
void Fare::setFareClass(FareClass fareClass) { 
    fareClass_ = fareClass;
}
void Fare::setTax(const string& tax) { 
    tax_ = tax; 
}
void Fare::setDiscounts(const string& discounts) { 
    discounts_ = discounts; 
}

const string& Fare::getFareCode() const { 
    return fareCode_; 
}
double Fare::getPrice() const {
    return price_;
}
FareClass Fare::getFareClass() const {
    return fareClass_;
}
const string& Fare::getTax() const {
    return tax_; 
}
const string& Fare::getDiscounts() const {
    return discounts_;
}

double Fare::calculateTotal(double taxRate) const {
    double total = price_ + (price_ * taxRate / 100);
    return total;
}

void Fare::applyDiscount(double percent) {
    if (percent > 0 && percent <= 100) price_ -= price_ * (percent / 100.0);
    else return;
}

bool Fare::isRefundable() const {
    return (fareClass_ == FareClass::Business || fareClass_ == FareClass::FirstClass);
}
