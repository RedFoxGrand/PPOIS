#include "AircraftModel.h"
#include <iomanip>

AircraftModel::AircraftModel(const string& modelName, int capacity,
    const string& manufacturer, double rangeKm, double fuelConsumption,
    const string& engineType, int speed) : 
    modelName_(modelName),
    capacity_(capacity),
    manufacturer_(manufacturer),
    rangeKm_(rangeKm),
    fuelConsumption_(fuelConsumption),
    engineType_(engineType),
    speed_(speed) {
}

void AircraftModel::setModelName(const string& modelName) { 
    modelName_ = modelName; 
}
void AircraftModel::setCapacity(int capacity) { 
    capacity_ = capacity; 
}
void AircraftModel::setManufacturer(const string& manufacturer) { 
    manufacturer_ = manufacturer; 
}
void AircraftModel::setRangeKm(double rangeKm) { 
    rangeKm_ = rangeKm; 
}
void AircraftModel::setFuelConsumption(double fuelConsumption) { 
    fuelConsumption_ = fuelConsumption; 
}
void AircraftModel::setEngineType(const string& engineType) { 
    engineType_ = engineType; 
}
void AircraftModel::setSpeed(int speed) { 
    speed_ = speed; 
}

const string& AircraftModel::getModelName() const { 
    return modelName_; 
}
int AircraftModel::getCapacity() const { 
    return capacity_; 
}
const string& AircraftModel::getManufacturer() const { 
    return manufacturer_; 
}
double AircraftModel::getRangeKm() const { 
    return rangeKm_; 
}
double AircraftModel::getFuelConsumption() const { 
    return fuelConsumption_; 
}
const string& AircraftModel::getEngineType() const { 
    return engineType_; 
}
int AircraftModel::getSpeed() const { 
    return speed_; 
}

double AircraftModel::estimateRange() const {
    double adjustedRange = rangeKm_ - (fuelConsumption_ * 0.1);
    return adjustedRange > 0 ? adjustedRange : 0.0;
}
