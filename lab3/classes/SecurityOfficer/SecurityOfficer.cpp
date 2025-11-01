#include "SecurityOfficer.h"

SecurityOfficer::SecurityOfficer(const string& name, const string& surname,
    time_t birthDate, const ContactInfo& contact, double salary, bool isAvailable,
    const string& badgeId, const string& assignedGate, const string& clearanceLevel) : 
    Employee(name, surname, birthDate, contact, salary, isAvailable),
    badgeId_(badgeId),
    assignedGate_(assignedGate),
    clearanceLevel_(clearanceLevel) {
}

void SecurityOfficer::setBadgeId(const string& badgeId) { 
    badgeId_ = badgeId; 
}
void SecurityOfficer::setAssignedGate(const string& assignedGate) { 
    assignedGate_ = assignedGate; 
}
void SecurityOfficer::setClearanceLevel(const string& clearanceLevel) {
    clearanceLevel_ = clearanceLevel; 
}

const string& SecurityOfficer::getBadgeId() const {
    return badgeId_;
}
const string& SecurityOfficer::getAssignedGate() const { 
    return assignedGate_;
}
const string& SecurityOfficer::getClearanceLevel() const { 
    return clearanceLevel_; 
}

bool SecurityOfficer::inspectPassenger(const Passenger& passenger) {
    bool passed = true;
    return passed;
}

void SecurityOfficer::reportIncident(const string& details) const {
    cout << "[ОТЧЁТ О ПРОИСШЕСТВИИ] Сотрудник " << getFullName() << " (" << badgeId_ << ") сообщил: " << details << endl;
}

