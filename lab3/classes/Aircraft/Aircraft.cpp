#include "Aircraft.h"
#include "Flight.h"
#include <ctime>

Aircraft::Aircraft(const string& tailNumber, const AircraftModel& model,
    int fuelLevel, AircraftStatus status, bool isAvailable) : 
    tailNumber_(tailNumber),
    model_(model),
    fuelLevel_(fuelLevel),
    status_(status),
    isAvailable_(isAvailable) {
}

void Aircraft::setTailNumber(const string& tailNumber) { 
    tailNumber_ = tailNumber; 
}
void Aircraft::setModel(const AircraftModel& model) { 
    model_ = model; 
}
void Aircraft::setFuelLevel(int fuelLevel) { 
    fuelLevel_ = fuelLevel; 
}
void Aircraft::setStatus(AircraftStatus status) { 
    status_ = status; 
}
void Aircraft::setIsAvailable(bool available) { 
    isAvailable_ = available; 
}

const string& Aircraft::getTailNumber() const { 
    return tailNumber_; 
}
const AircraftModel& Aircraft::getModel() const { 
    return model_; 
}
int Aircraft::getFuelLevel() const { 
    return fuelLevel_; 
}
AircraftStatus Aircraft::getStatus() const { 
    return status_; 
}
bool Aircraft::getIsAvailable() const { 
    return isAvailable_; 
}

void Aircraft::refuel(int liters) {
    if (liters <= 0) throw InvalidFuelException("Количество топлива не может быть отрицательным");
    fuelLevel_ += liters;
}

void Aircraft::assignFlight(const Flight& flight) {
    status_ = AircraftStatus::ScheduledForFlight;
    isAvailable_ = false;
}

Schedule Aircraft::scheduleMaintenance() {
    status_ = AircraftStatus::UnderMaintenance;
    isAvailable_ = false;

    time_t now = time(nullptr);
    Schedule maintenanceSchedule({}, now, now + 86400, now + 90000, now, false);

    return maintenanceSchedule;
}
