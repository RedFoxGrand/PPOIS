#include "AirTrafficController.h"

AirTrafficController::AirTrafficController(const string& name, const string& surname,
    time_t birthDate, const ContactInfo& contact, double salary,
    bool isAvailable, const string& stationCode, const string& controlZone) : 
    Employee(name, surname, birthDate, contact, salary, isAvailable),
    stationCode_(stationCode),
    controlZone_(controlZone) {
}

void AirTrafficController::setStationCode(const string& stationCode) { 
    stationCode_ = stationCode; 
}
void AirTrafficController::setControlZone(const string& controlZone) { 
    controlZone_ = controlZone; 
}

const string& AirTrafficController::getStationCode() const { 
    return stationCode_; 
}
const string& AirTrafficController::getControlZone() const { 
    return controlZone_; 
}