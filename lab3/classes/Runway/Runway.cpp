#include "Runway.h"

Runway::Runway(const string& code, bool isAvailable, double length, RunwayStatus status) : 
    code_(code),
    isAvailable_(isAvailable),
    length_(length),
    status_(status) {
}

void Runway::setCode(const string& code) { 
    code_ = code;
}
void Runway::setIsAvailable(bool isAvailable) {
    isAvailable_ = isAvailable;
}
void Runway::setLength(double length) { 
    length_ = length;
}
void Runway::setStatus
(RunwayStatus status) { 
    status_ = status; }

const string& Runway::getCode() const {
    return code_; 
}
bool Runway::getIsAvailable() const { 
    return isAvailable_; 
}
double Runway::getLength() const { 
    return length_; 
}
RunwayStatus Runway::getStatus() const { 
    return status_; 
}

void Runway::reserveRunway() {
    if (!isAvailable_) return;
    status_ = RunwayStatus::Reserved;
    isAvailable_ = false;
}

void Runway::releaseRunway() {
    status_ = RunwayStatus::Available;
    isAvailable_ = true;
}

Schedule Runway::scheduleTakeoff(const string& flightNumber) {
    Schedule schedule({}, time(nullptr), time(nullptr) + 3600, time(nullptr) + 7200, time(nullptr), false);
    schedule.addFlight(flightNumber);

    status_ = RunwayStatus::Occupied;
    isAvailable_ = false;
    return schedule;
}

Schedule Runway::scheduleLanding(const string& flightNumber) {
    Schedule schedule({}, time(nullptr), time(nullptr) + 1800, time(nullptr) + 5400, time(nullptr), false);
    schedule.addFlight(flightNumber);

    status_ = RunwayStatus::Occupied;
    isAvailable_ = false;
    return schedule;
}

