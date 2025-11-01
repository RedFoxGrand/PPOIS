#include "Airport.h"

Airport::Airport(const string& name, const string& location,
    const vector<Runway>& runways, const vector<Gate>& gates) : 
    name_(name), 
    location_(location), 
    runways_(runways), 
    gates_(gates) {
}

void Airport::setName(const string& name) { 
    name_ = name; 
}
void Airport::setLocation(const string& location) { 
    location_ = location; 
}
void Airport::setRunways(const vector<Runway>& runways) { 
    runways_ = runways; 
}
void Airport::setGates(const vector<Gate>& gates) { 
    gates_ = gates; 
}

const string& Airport::getName() const { 
    return name_; 
}
const string& Airport::getLocation() const { 
    return location_; 
}
const vector<Runway>& Airport::getRunways() const { 
    return runways_; 
}
const vector<Gate>& Airport::getGates() const { 
    return gates_; 
}

bool Airport::findGate(const string& gateNumber) const {
    for (const auto& gate : gates_) {
        if (gate.getGateNumber() == gateNumber) return true;
    }
    return false;
}

void Airport::assignGate(const Flight& flight) {
    for (auto& gate : gates_) {
        if (!gate.getIsOccupied()) {
            gate.assignFlight(flight.getFlightNumber());
            return;
        }
    }
}

void Airport::assignRunwayToFlight(const Flight& flight) {
    for (auto& runway : runways_) {
        if (runway.getIsAvailable()) {
            runway.reserveRunway();
            return;
        }
    }
}
