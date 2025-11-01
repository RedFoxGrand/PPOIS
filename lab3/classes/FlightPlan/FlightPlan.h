#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Flight.h"
#include "Airport.h"
#include "WeatherCondition.h"

using namespace std;

class FlightPlan {
public:
    FlightPlan(const Flight& flight, const vector<Airport>& checkpoints,
        const WeatherCondition& weather, int altitude);

    void setFlight(const Flight& flight);
    void setCheckpoints(const vector<Airport>& checkpoints);
    void setWeather(const WeatherCondition& weather);
    void setAltitude(int altitude);

    const Flight& getFlight() const;
    const vector<Airport>& getCheckpoints() const;
    const WeatherCondition& getWeather() const;
    int getAltitude() const;

    void updateFlight(const vector<Airport>& newFlight);
    void printPlan() const;

private:
    Flight flight_;
    vector<Airport> checkpoints_;
    WeatherCondition weather_;
    int altitude_;
};
