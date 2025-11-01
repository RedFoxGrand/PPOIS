#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "Aircraft.h"
#include "InvalidFuelException.h"

using namespace std;

class FuelRecord {
public:
    FuelRecord(const string& refuelId, const Aircraft& aircraft, 
        double liters, time_t timestamp);

    void setRefuelId(const string& refuelId);
    void setAircraft(const Aircraft& aircraft);
    void setLiters(double liters);
    void setTimestamp(time_t timestamp);

    const string& getRefuelId() const;
    const Aircraft& getAircraft() const;
    double getLiters() const;
    time_t getTimestamp() const;

    void addFuel(double liters);

private:
    string refuelId_;
    Aircraft aircraft_;
    double liters_;
    time_t timestamp_;
};
