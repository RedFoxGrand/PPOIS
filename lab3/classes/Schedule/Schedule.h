#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include "FlightNotFound.h"

using namespace std;

class Schedule {
public:
    Schedule(const vector<string>& flightNumbers, time_t lastUpdate, time_t departureTime,
        time_t arrivalTime, time_t date, bool isRecurring);

    void setFlightNumbers(const vector<string>& flightNumbers);
    void setLastUpdate(time_t lastUpdate);
    void setDepartureTime(time_t departureTime);
    void setArrivalTime(time_t arrivalTime);
    void setDate(time_t date);
    void setIsRecurring(bool isRecurring);

    const vector<string>& getFlightNumbers() const;
    time_t getLastUpdate() const;
    time_t getDepartureTime() const;
    time_t getArrivalTime() const;
    time_t getDate() const;
    bool getIsRecurring() const;

    void addFlight(const string& flightNumber);
    void removeFlight(const string& flightNumber);
    string findFlightByNumber(const string& flightNumber) const;
    bool isDelayed() const;

private:
    vector<string> flightNumbers_;
    time_t lastUpdate_;
    time_t departureTime_;
    time_t arrivalTime_;
    time_t date_;
    bool isRecurring_;
};
