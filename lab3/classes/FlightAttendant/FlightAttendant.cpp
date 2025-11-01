#include "FlightAttendant.h"

FlightAttendant::FlightAttendant(const string& name, const string& surname,
    time_t birthDate, const ContactInfo& data, double salary, bool isAvailable,
    int serviceYears, const vector<string>& languages) : 
    Employee(name, surname, birthDate, data, salary, isAvailable),
    serviceYears_(serviceYears),
    languages_(languages) {
}

void FlightAttendant::setServiceYears(int years) {
    serviceYears_ = years; 
}
void FlightAttendant::setLanguages(const vector<string>& languages) { 
    languages_ = languages; 
}

int FlightAttendant::getServiceYears() const { 
    return serviceYears_;
}
const vector<string>& FlightAttendant::getLanguages() const { 
    return languages_; 
}

void FlightAttendant::addLanguage(const string& language) { 
    languages_.push_back(language); 
}