#pragma once
#include <iostream>
#include <string>
#include "Employee.h"
#include "Gate.h"
#include "Passenger.h"
#include "Cargo.h"

using namespace std;

class GroundStaff : public Employee {
public:
    GroundStaff(const string& name, const string& surname, time_t birthDate,
        const ContactInfo& data, double salary, bool isAvailable,
        const Gate& assignedGate, const string& area, bool onDuty);

    void setAssignedGate(const Gate& gate);
    void setArea(const string& area);
    void setOnDuty(bool status);

    const Gate& getAssignedGate() const;
    const string& getArea() const;
    bool isOnDuty() const;

protected:
    Gate assignedGate_;
    string area_;
    bool onDuty_;
};
