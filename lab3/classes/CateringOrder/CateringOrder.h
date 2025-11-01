#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Passenger.h"
#include "InvalidBalanceException.h"

using namespace std;

class CateringOrder {
public:
    CateringOrder(const Passenger& passenger, const vector<string>& items,
        double totalCost, bool isDelivered, time_t orderTime);

    void setPassenger(const Passenger& passenger);
    void setItems(const vector<string>& items);
    void setTotalCost(double totalCost);
    void setDelivered(bool delivered);
    void setOrderTime(time_t orderTime);

    const Passenger& getPassenger() const;
    const vector<string>& getItems() const;
    double getTotalCost() const;
    bool getIsDelivered() const;
    time_t getOrderTime() const;

    void addItem(const string& item);
    void calculateTotalPrice(double pricePerItem);

private:
    Passenger passenger_;
    vector<string> items_;
    double totalCost_;
    bool isDelivered_;
    time_t orderTime_;
};
