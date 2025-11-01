#include "FlightPlan.h"

FlightPlan::FlightPlan(const Flight& flight, const vector<Airport>& checkpoints,
    const WeatherCondition& weather, int altitude) : 
    flight_(flight), 
    checkpoints_(checkpoints), 
    weather_(weather), 
    altitude_(altitude) {
}

void FlightPlan::setFlight(const Flight& flight) { 
    flight_ = flight; 
}
void FlightPlan::setCheckpoints(const vector<Airport>& checkpoints) { 
    checkpoints_ = checkpoints; 
}
void FlightPlan::setWeather(const WeatherCondition& weather) { 
    weather_ = weather; 
}
void FlightPlan::setAltitude(int altitude) { 
    altitude_ = altitude; 
}

const Flight& FlightPlan::getFlight() const {
    return flight_; 
}
const vector<Airport>& FlightPlan::getCheckpoints() const {
    return checkpoints_;
}
const WeatherCondition& FlightPlan::getWeather() const { 
    return weather_; 
}
int FlightPlan::getAltitude() const {
    return altitude_; 
}

void FlightPlan::updateFlight(const vector<Airport>& newFlight) {
    checkpoints_ = newFlight;
    cout << "   Общее количество контрольных точек: " << checkpoints_.size() << endl;
}

void FlightPlan::printPlan() const {
    cout << "   План полёта для рейса " << flight_.getFlightNumber() << ":\n";
    cout << "   Маршрут: " << flight_.getOrigin() << " -> " << flight_.getDestination() << endl;
    cout << "   Высота полёта: " << altitude_ << " футов\n";
    cout << "   Погодные условия: " << weather_.getCondition()
        << " (уровень тревоги: " << weather_.getAlertLevel() << ")\n";
    cout << "   Контрольные точки:\n";

    if (checkpoints_.empty()) cout << "   - Контрольные точки не заданы.\n";
    else for (const auto& airport : checkpoints_) {
            cout << "   - " << airport.getName() << " (" << airport.getLocation() << ")\n";
        }
    cout << endl;
}

