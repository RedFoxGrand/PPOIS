#include "GroundStaff.h"

GroundStaff::GroundStaff(const string& name, const string& surname, time_t birthDate,
    const ContactInfo& data, double salary, bool isAvailable,
    const Gate& assignedGate, const string& area, bool onDuty) : 
    Employee(name, surname, birthDate, data, salary, isAvailable),
    assignedGate_(assignedGate),
    area_(area),
    onDuty_(onDuty) {
}

void GroundStaff::setAssignedGate(const Gate& gate) { 
    assignedGate_ = gate;
}
void GroundStaff::setArea(const string& area) {
    area_ = area; 
}
void GroundStaff::setOnDuty(bool status) { 
    onDuty_ = status; 
}

const Gate& GroundStaff::getAssignedGate() const { 
    return assignedGate_; 
}
const string& GroundStaff::getArea() const { 
    return area_; 
}
bool GroundStaff::isOnDuty() const { 
    return onDuty_; 
}