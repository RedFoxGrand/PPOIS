#include "Hangar.h"

Hangar::Hangar(const string& location, int capacity, bool isOccupied, const vector<Aircraft>& storedAircraft) : 
    location_(location), 
    capacity_(capacity), 
    isOccupied_(isOccupied), 
    storedAircraft_(storedAircraft){
}

void Hangar::setLocation(const string& location) {
    location_ = location; 
}
void Hangar::setCapacity(int capacity) {
    capacity_ = capacity;
}
void Hangar::setOccupied(bool isOccupied) { 
    isOccupied_ = isOccupied; 
}
void Hangar::setStoredAircraft(const vector<Aircraft>& aircraftList) {
    storedAircraft_ = aircraftList; 
}

const string& Hangar::getLocation() const { 
    return location_; 
}
int Hangar::getCapacity() const { 
    return capacity_; 
}
bool Hangar::getIsOccupied() const {
    return isOccupied_; 
}
const vector<Aircraft>& Hangar::getStoredAircraft() const {
    return storedAircraft_;
}

void Hangar::storeAircraft(const Aircraft& aircraft) {
    if (storedAircraft_.size() >= static_cast<size_t>(capacity_)) throw InvalidCapacityException("Ангар полностью заполнен");
    storedAircraft_.push_back(aircraft);
    isOccupied_ = true;
}

void Hangar::releaseAircraft(const Aircraft& aircraft) {
    for (auto it = storedAircraft_.begin(); it != storedAircraft_.end(); ++it) {
        if (it->getTailNumber() == aircraft.getTailNumber()) {
            storedAircraft_.erase(it);
            break;
        }
    }

    if (storedAircraft_.empty()) isOccupied_ = false;
}

