#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Gate.h"
#include "Runway.h"
#include "Flight.h"

using namespace std;

class Airport {
public:
    Airport(const string& name, const string& location, 
        const vector<Runway>& runways, const vector<Gate>& gates);

    void setName(const string& name);
    void setLocation(const string& location);
    void setRunways(const vector<Runway>& runways);
    void setGates(const vector<Gate>& gates);

    const string& getName() const;
    const string& getLocation() const;
    const vector<Runway>& getRunways() const;
    const vector<Gate>& getGates() const;

    bool findGate(const string& gateNumber) const;
    void assignGate(const Flight& flight);
    void assignRunwayToFlight(const Flight& flight);

private:
    string name_;
    vector<Runway> runways_;
    vector<Gate> gates_;
    string location_;
};
