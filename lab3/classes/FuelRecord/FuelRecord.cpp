#include "FuelRecord.h"

FuelRecord::FuelRecord(const string& refuelId, const Aircraft& aircraft, double liters, time_t timestamp) : 
    refuelId_(refuelId), 
    aircraft_(aircraft), 
    liters_(liters), 
    timestamp_(timestamp) {
}

void FuelRecord::setRefuelId(const string& refuelId) { 
    refuelId_ = refuelId;
}
void FuelRecord::setAircraft(const Aircraft& aircraft) {
    aircraft_ = aircraft; 
}
void FuelRecord::setLiters(double liters) { 
    liters_ = liters; 
}
void FuelRecord::setTimestamp(time_t timestamp) { 
    timestamp_ = timestamp; 
}

const string& FuelRecord::getRefuelId() const { 
    return refuelId_; 
}
const Aircraft& FuelRecord::getAircraft() const { 
    return aircraft_;
}
double FuelRecord::getLiters() const {
    return liters_; 
}
time_t FuelRecord::getTimestamp() const {
    return timestamp_; 
}

void FuelRecord::addFuel(double liters) {
    if (liters <= 0) throw InvalidFuelException("Количество топлива не может быть отрицательным");

    liters_ += liters;
    time(&timestamp_);
}

