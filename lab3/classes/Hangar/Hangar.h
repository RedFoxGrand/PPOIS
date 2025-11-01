#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Aircraft.h"
#include "InvalidCapacityException.h"

using namespace std;

class Hangar {
public:
    Hangar(const string& location, int capacity, bool isOccupied, 
        const vector<Aircraft>& storedAircraft);

    void setLocation(const string& location);
    void setCapacity(int capacity);
    void setOccupied(bool isOccupied);
    void setStoredAircraft(const vector<Aircraft>& aircraftList);

    const string& getLocation() const;
    int getCapacity() const;
    bool getIsOccupied() const;
    const vector<Aircraft>& getStoredAircraft() const;

    void storeAircraft(const Aircraft& aircraft);
    void releaseAircraft(const Aircraft& aircraft);

private:
    string location_;
    int capacity_;
    bool isOccupied_;
    vector<Aircraft> storedAircraft_;
};
