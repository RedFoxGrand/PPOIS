#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Baggage.h"

using namespace std;

class ConveyorBelt {
public:
    ConveyorBelt(const string& location, bool isActive, 
        const vector<Baggage>& currentBaggage, double speed, int capacity);

    void setLocation(const string& location);
    void setActive(bool isActive);
    void setSpeed(double speed);
    void setCapacity(int capacity);
    void setCurrentBaggage(const vector<Baggage>& baggage);

    const string& getLocation() const;
    bool getIsActive() const;
    double getSpeed() const;
    int getCapacity() const;
    const vector<Baggage>& getCurrentBaggage() const;

    void start();
    void stop();
    void unloadBaggage(const string& baggageId);
    void adjustSpeed(double newSpeed);
    bool isOverloaded() const;

private:
    string location_;
    bool isActive_;
    vector<Baggage> currentBaggage_;
    double speed_;
    int capacity_;
};
