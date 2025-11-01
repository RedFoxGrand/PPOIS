#include "Shift.h"
#include <cmath>

Shift::Shift(const Employee& employee, time_t startTime, time_t endTime, bool isActive) : 
    employee_(employee), 
    startTime_(startTime), 
    endTime_(endTime), 
    isActive_(isActive) {
}

void Shift::setEmployee(const Employee& employee) { 
    employee_ = employee;
}
void Shift::setStartTime(time_t startTime) { 
    startTime_ = startTime; 
}
void Shift::setEndTime(time_t endTime) { 
    endTime_ = endTime; 
}
void Shift::setActive(bool isActive) {
    isActive_ = isActive; 
}

const Employee& Shift::getEmployee() const { 
    return employee_; 
}
time_t Shift::getStartTime() const {
    return startTime_;
}
time_t Shift::getEndTime() const {
    return endTime_;
}
bool Shift::getIsActive() const {
    return isActive_; 
}

void Shift::startShift() {
    startTime_ = time(nullptr);
    isActive_ = true;
}

void Shift::endShift() {
    endTime_ = time(nullptr);
    isActive_ = false;
}

double Shift::getDurationHours() const {
    if (endTime_ < startTime_) return 0.0;
    double seconds = difftime(endTime_, startTime_);
    return round((seconds / 3600.0) * 100) / 100;
}

bool Shift::isOngoing() const {
    return isActive_;
}
