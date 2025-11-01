#pragma once
#include <iostream>
#include <string>
#include "GroundStaff.h"
#include "Baggage.h"

using namespace std;

class BaggageHandler : public GroundStaff {
public:
    BaggageHandler(const string& name, const string& surname, time_t birthDate,
        const ContactInfo& data, double salary, bool isAvailable,
        const Gate& assignedGate, const string& area, bool onDuty, int experienceYears);

    void setExperienceYears(int years);

    int getExperienceYears() const;

private:
    int experienceYears_;
};
