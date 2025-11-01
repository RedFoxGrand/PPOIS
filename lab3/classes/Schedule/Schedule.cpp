#include "Schedule.h"

// Конструктор
Schedule::Schedule(const vector<string>& flightNumbers, time_t lastUpdate,
    time_t departureTime, time_t arrivalTime, time_t date, bool isRecurring) : 
    flightNumbers_(flightNumbers),
    lastUpdate_(lastUpdate),
    departureTime_(departureTime),
    arrivalTime_(arrivalTime),
    date_(date),
    isRecurring_(isRecurring) {
}

void Schedule::setFlightNumbers(const vector<string>& flightNumbers) {
    flightNumbers_ = flightNumbers; 
}
void Schedule::setLastUpdate(time_t lastUpdate) { 
    lastUpdate_ = lastUpdate; 
}
void Schedule::setDepartureTime(time_t departureTime) { 
    departureTime_ = departureTime; 
}
void Schedule::setArrivalTime(time_t arrivalTime) { 
    arrivalTime_ = arrivalTime;
}
void Schedule::setDate(time_t date) { 
    date_ = date; 
}
void Schedule::setIsRecurring(bool isRecurring) { 
    isRecurring_ = isRecurring; 
}

const vector<string>& Schedule::getFlightNumbers() const { 
    return flightNumbers_; 
}
time_t Schedule::getLastUpdate() const { 
    return lastUpdate_; 
}
time_t Schedule::getDepartureTime() const { 
    return departureTime_; 
}
time_t Schedule::getArrivalTime() const { 
    return arrivalTime_; 
}
time_t Schedule::getDate() const { 
    return date_; }
bool Schedule::getIsRecurring() const { 
    return isRecurring_; 
}

void Schedule::addFlight(const string& flightNumber) {
    if (find(flightNumbers_.begin(), flightNumbers_.end(), flightNumber) == flightNumbers_.end()) {
        flightNumbers_.push_back(flightNumber);
        lastUpdate_ = time(nullptr);
    }
    else return;
}

void Schedule::removeFlight(const string& flightNumber) {
    auto it = remove(flightNumbers_.begin(), flightNumbers_.end(), flightNumber);
    if (it != flightNumbers_.end()) {
        flightNumbers_.erase(it, flightNumbers_.end());
        lastUpdate_ = time(nullptr);
    }
    else return;
}

string Schedule::findFlightByNumber(const string& flightNumber) const {
    auto it = find(flightNumbers_.begin(), flightNumbers_.end(), flightNumber);
    if (it != flightNumbers_.end()) return *it;
    else throw FlightNotFound("Рейс не найден");
}

bool Schedule::isDelayed() const {
    time_t now = time(nullptr);
    bool delayed = now > departureTime_;
    return delayed;
}
