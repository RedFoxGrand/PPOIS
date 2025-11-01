#include "FlightManager.h"

FlightManager::FlightManager(const vector<Flight>& flights) : 
    flights_(flights) {
}

void FlightManager::setFlights(const vector<Flight>& flights) {
    flights_ = flights;
}

const vector<Flight>& FlightManager::getFlights() const {
    return flights_;
}

void FlightManager::createFlight(const Flight& flight) {
    flights_.push_back(flight);
}

void FlightManager::cancelFlight(const string& flightNumber) {
    for (auto it = flights_.begin(); it != flights_.end(); it++) {
        if (it->getFlightNumber() == flightNumber) {
            flights_.erase(it);
            return;
        }
    }
}
