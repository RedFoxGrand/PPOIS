#pragma once
#include <iostream>
#include <string>
#include "Passenger.h"

using namespace std;

class Cargo {
public:
    Cargo(double weight, const string& description, const Passenger& owner);

    void setWeight(double weight);
    void setDescription(const string& description);
    void setOwner(const Passenger& owner);

    double getWeight() const;
    const string& getDescription() const;
    const Passenger& getOwner() const;

private:
    double weight_;
    string description_;
    Passenger owner_;
};
