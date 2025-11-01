#include "BaggageHandler.h"

BaggageHandler::BaggageHandler(const string& name, const string& surname,
    time_t birthDate, const ContactInfo& data, double salary, bool isAvailable,
    const Gate& assignedGate, const string& area, bool onDuty, int experienceYears) : 
    GroundStaff(name, surname, birthDate, data, salary, isAvailable, assignedGate, area, onDuty),
    experienceYears_(experienceYears) {
}

void BaggageHandler::setExperienceYears(int years) { 
    experienceYears_ = years; 
}

int BaggageHandler::getExperienceYears() const { 
    return experienceYears_; 
}