#include "Gate.h"

Gate::Gate(const string& gateNumber, bool isOccupied, const string& assignedFlightNumber) : 
    gateNumber_(gateNumber),
    isOccupied_(isOccupied),
    assignedFlightNumber_(assignedFlightNumber) {
}

void Gate::setGateNumber(const string& gateNumber) { 
    gateNumber_ = gateNumber; 
}
void Gate::setIsOccupied(bool isOccupied) { 
    isOccupied_ = isOccupied; 
}
void Gate::setAssignedFlightNumber(const string& assignedFlightNumber) {
    assignedFlightNumber_ = assignedFlightNumber;
}

const string& Gate::getGateNumber() const { 
    return gateNumber_; 
}
bool Gate::getIsOccupied() const {
    return isOccupied_; 
}
const string& Gate::getAssignedFlightNumber() const {
    return assignedFlightNumber_; 
}

void Gate::assignFlight(const string& flightNumber) {
    if (isOccupied_) return;
    assignedFlightNumber_ = flightNumber;
    isOccupied_ = true;
}

void Gate::freeGate() {
    if (!isOccupied_) return;
    assignedFlightNumber_.clear();
    isOccupied_ = false;
}

void Gate::markClosed() {
    assignedFlightNumber_ = "CLOSED";
    isOccupied_ = true;
}

Gate Gate::findFreeGate(const vector<Gate>& gates) {
    for (const auto& gate : gates) {
        if (!gate.getIsOccupied()) return gate;
    }
    return Gate("N/A", true, "None");
}

