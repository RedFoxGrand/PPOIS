#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Flight.h"
#include "Employee.h"

using namespace std;

class FlightManager {
public:
    FlightManager(const vector<Flight>& flights);

    void setFlights(const vector<Flight>& flights);

    const vector<Flight>& getFlights() const;

    void createFlight(const Flight& flight);
    void cancelFlight(const string& flightNumber);

private:
    vector<Flight> flights_;
};
