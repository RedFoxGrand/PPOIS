#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Gate {
public:
    Gate(const string& gateNumber, bool isOccupied, const string& assignedFlightNumber);

    void setGateNumber(const string& gateNumber);
    void setIsOccupied(bool isOccupied);
    void setAssignedFlightNumber(const string& assignedFlightNumber);

    const string& getGateNumber() const;
    bool getIsOccupied() const;
    const string& getAssignedFlightNumber() const;

    void assignFlight(const string& flightNumber);
    void freeGate();
    void markClosed();
    static Gate findFreeGate(const vector<Gate>& gates);

private:
    string gateNumber_;
    bool isOccupied_;
    string assignedFlightNumber_;
};
