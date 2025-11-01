#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "Aircraft.h"
#include "Schedule.h"

using namespace std;

class Flight {
public:
    Flight(const string& flightNumber, const string& origin, 
        const string& destination, const Aircraft& aircraft, const Schedule& schedule, 
        double distanceKm, const vector<string>& passengerIds);

    void setFlightNumber(const string& flightNumber);
    void setOrigin(const string& origin);
    void setDestination(const string& destination);
    void setAircraft(const Aircraft& aircraft);
    void setSchedule(const Schedule& schedule);
    void setDistanceKm(double distanceKm);
    void setPassengerIds(const vector<string>& passengerIds);

    const string& getFlightNumber() const;
    const string& getOrigin() const;
    const string& getDestination() const;
    const Aircraft& getAircraft() const;
    const Schedule& getSchedule() const;
    double getDistanceKm() const;
    const vector<string>& getPassengerIds() const;

    void addPassenger(const string& passengerId);
    double calculateFlightTime(const AircraftModel& model) const;

private:
    string flightNumber_;
    string origin_;
    string destination_;
    Aircraft aircraft_;
    Schedule schedule_;
    double distanceKm_;
    vector<string> passengerIds_;
};
