#pragma once
#include <iostream>
#include <string>
#include "Employee.h"
#include "Flight.h"
#include "AircraftModel.h"

using namespace std;

class Pilot : public Employee {
public:
    Pilot(const string& name, const string& surname, time_t birthDate,
        const ContactInfo& data, double salary, bool isAvailable,
        const string& licenseNumber, int flightHours);

    void setLicenseNumber(const string& licenseNumber);
    void setFlightHours(int flightHours);

    const string& getLicenseNumber() const;
    int getFlightHours() const;

    void updateHours(int hours);
    bool isCertifiedFor(const AircraftModel& model) const;

private:
    string licenseNumber_;
    int flightHours_;
};
