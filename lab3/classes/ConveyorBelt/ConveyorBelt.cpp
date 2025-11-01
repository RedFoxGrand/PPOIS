#include "ConveyorBelt.h"

ConveyorBelt::ConveyorBelt(const string& location, bool isActive, 
    const vector<Baggage>& currentBaggage, double speed, int capacity) : 
    location_(location), 
    isActive_(isActive), 
    currentBaggage_(currentBaggage), 
    speed_(speed), 
    capacity_(capacity) {
}

void ConveyorBelt::setLocation(const string& location) { 
    location_ = location; 
}
void ConveyorBelt::setActive(bool isActive) { 
    isActive_ = isActive; 
}
void ConveyorBelt::setSpeed(double speed) { 
    speed_ = speed;
}
void ConveyorBelt::setCapacity(int capacity) { 
    capacity_ = capacity; 
}
void ConveyorBelt::setCurrentBaggage(const vector<Baggage>& baggage) { 
    currentBaggage_ = baggage; 
}

const string& ConveyorBelt::getLocation() const { 
    return location_; 
}
bool ConveyorBelt::getIsActive() const { 
    return isActive_; 
}
double ConveyorBelt::getSpeed() const { 
    return speed_; 
}
int ConveyorBelt::getCapacity() const { 
    return capacity_; 
}
const vector<Baggage>& ConveyorBelt::getCurrentBaggage() const { 
    return currentBaggage_; 
}

void ConveyorBelt::start() {
    if (!isActive_) isActive_ = true;
}

void ConveyorBelt::stop() {
    if (isActive_) isActive_ = false;
}

void ConveyorBelt::unloadBaggage(const string& baggageId) {
    for (auto it = currentBaggage_.begin(); it != currentBaggage_.end(); ++it) {
        if (it->getBaggageId() == baggageId) {
            currentBaggage_.erase(it);
            return;
        }
    }
}

void ConveyorBelt::adjustSpeed(double newSpeed) {
    if (newSpeed <= 0) return;
    speed_ = newSpeed;
}

bool ConveyorBelt::isOverloaded() const {
    bool overloaded = currentBaggage_.size() >= static_cast<size_t>(capacity_);
    return overloaded;
}