#pragma once
#include <iostream>
#include <string>
#include "Employee.h"
#include "Flight.h"

using namespace std;

class AirTrafficController : public Employee {
public:
    AirTrafficController(const string& name, const string& surname, time_t birthDate, 
        const ContactInfo& contact, double salary, bool isAvailable, 
        const string& stationCode, const string& controlZone);

    void setStationCode(const string& stationCode);
    void setControlZone(const string& controlZone);

    const string& getStationCode() const;
    const string& getControlZone() const;

private:
    string stationCode_;
    string controlZone_;
};
