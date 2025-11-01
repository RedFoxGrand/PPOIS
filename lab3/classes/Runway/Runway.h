#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "Schedule.h"

using namespace std;

enum class RunwayStatus { Available, Occupied, UnderMaintenance, Closed, Reserved };

class Runway {
public:
    Runway(const string& code, bool isAvailable, double length, RunwayStatus status);

    void setCode(const string& code);
    void setIsAvailable(bool isAvailable);
    void setLength(double length);
    void setStatus(RunwayStatus status);

    const string& getCode() const;
    bool getIsAvailable() const;
    double getLength() const;
    RunwayStatus getStatus() const;

    void reserveRunway();
    void releaseRunway();
    Schedule scheduleTakeoff(const string& flightNumber);
    Schedule scheduleLanding(const string& flightNumber);

private:
    string code_;
    bool isAvailable_;
    double length_;
    RunwayStatus status_;
};
