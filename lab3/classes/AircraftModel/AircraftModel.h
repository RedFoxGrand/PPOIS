#pragma once
#include <iostream>
#include <string>

using namespace std;

class AircraftModel {
public:
    AircraftModel(const string& modelName, int capacity, const string& manufacturer,
        double rangeKm, double fuelConsumption, const string& engineType, int speed);

    void setModelName(const string& modelName);
    void setCapacity(int capacity);
    void setManufacturer(const string& manufacturer);
    void setRangeKm(double rangeKm);
    void setFuelConsumption(double fuelConsumption);
    void setEngineType(const string& engineType);
    void setSpeed(int speed);

    const string& getModelName() const;
    int getCapacity() const;
    const string& getManufacturer() const;
    double getRangeKm() const;
    double getFuelConsumption() const;
    const string& getEngineType() const;
    int getSpeed() const;

    double estimateRange() const;

private:
    string modelName_;
    int capacity_;
    string manufacturer_;
    double rangeKm_;
    double fuelConsumption_;
    string engineType_;
    int speed_;
};
