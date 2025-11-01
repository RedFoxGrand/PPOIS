#pragma once
#include <iostream>
#include <string>
#include "Employee.h"
#include "Passenger.h"

using namespace std;

class SecurityOfficer : public Employee {
public:
    SecurityOfficer(const string& name, const string& surname,
        time_t birthDate, const ContactInfo& contact, double salary, 
        bool isAvailable, const string& badgeId,
        const string& assignedGate, const string& clearanceLevel);

    void setBadgeId(const string& badgeId);
    void setAssignedGate(const string& assignedGate);
    void setClearanceLevel(const string& clearanceLevel);

    const string& getBadgeId() const;
    const string& getAssignedGate() const;
    const string& getClearanceLevel() const;

    bool inspectPassenger(const Passenger& passenger);
    void reportIncident(const string& details) const;

private:
    string badgeId_;
    string assignedGate_;
    string clearanceLevel_;
};
