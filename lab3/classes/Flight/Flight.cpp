#include "Flight.h"

Flight::Flight(const string& flightNumber, const string& origin,
    const string& destination, const Aircraft& aircraft,
    const Schedule& schedule, double distanceKm, const vector<string>& passengerIds) : 
    flightNumber_(flightNumber),
    origin_(origin),
    destination_(destination),
    aircraft_(aircraft),
    schedule_(schedule),
    distanceKm_(distanceKm), passengerIds_(passengerIds){
}

void Flight::setFlightNumber(const string& flightNumber) { 
    flightNumber_ = flightNumber; 
}
void Flight::setOrigin(const string& origin) { 
    origin_ = origin; 
}
void Flight::setDestination(const string& destination) { 
    destination_ = destination; 
}
void Flight::setAircraft(const Aircraft& aircraft) { 
    aircraft_ = aircraft; 
}
void Flight::setSchedule(const Schedule& schedule) { 
    schedule_ = schedule; 
}
void Flight::setDistanceKm(double distanceKm) {
    distanceKm_ = distanceKm; 
}
void Flight::setPassengerIds(const vector<string>& passengerIds) { 
    passengerIds_ = passengerIds;
}

const string& Flight::getFlightNumber() const {
    return flightNumber_; 
}
const string& Flight::getOrigin() const {
    return origin_; 
}
const string& Flight::getDestination() const {
    return destination_; 
}
const Aircraft& Flight::getAircraft() const {
    return aircraft_; 
}
const Schedule& Flight::getSchedule() const {
    return schedule_; 
}
double Flight::getDistanceKm() const {
    return distanceKm_;
}
const vector<string>& Flight::getPassengerIds() const { 
    return passengerIds_; 
}

void Flight::addPassenger(const string& passengerId) {
    passengerIds_.push_back(passengerId);
}

double Flight::calculateFlightTime(const AircraftModel& model) const {
    if (model.getSpeed() <= 0) return 0.0;
    double timeHours = distanceKm_ / model.getSpeed();
    return timeHours;
}

