#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "Employee.h"

using namespace std;

class Shift {
public:
    Shift(const Employee& employee, time_t startTime, time_t endTime, bool isActive);

    void setEmployee(const Employee& employee);
    void setStartTime(time_t startTime);
    void setEndTime(time_t endTime);
    void setActive(bool isActive);

    const Employee& getEmployee() const;
    time_t getStartTime() const;
    time_t getEndTime() const;
    bool getIsActive() const;

    void startShift();
    void endShift();
    double getDurationHours() const;
    bool isOngoing() const;

private:
    Employee employee_;
    time_t startTime_;
    time_t endTime_;
    bool isActive_;
};
