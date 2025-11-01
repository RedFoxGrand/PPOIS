#include "Pilot.h"

Pilot::Pilot(const string& name, const string& surname,
    time_t birthDate, const ContactInfo& data, double salary,
    bool isAvailable, const string& licenseNumber, int flightHours) : 
    Employee(name, surname, birthDate, data, salary, isAvailable),
    licenseNumber_(licenseNumber),
    flightHours_(flightHours) {
}

void Pilot::setLicenseNumber(const string& licenseNumber) {
    licenseNumber_ = licenseNumber;
}
void Pilot::setFlightHours(int flightHours) { 
    flightHours_ = flightHours; 
}

const string& Pilot::getLicenseNumber() const {
    return licenseNumber_; 
}
int Pilot::getFlightHours() const {
    return flightHours_; 
}

void Pilot::updateHours(int hours) {
    flightHours_ += hours;
}

bool Pilot::isCertifiedFor(const AircraftModel& model) const {
    if (flightHours_ > 1000) return true;
    else return false;
}

