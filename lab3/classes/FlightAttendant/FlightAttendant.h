#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Employee.h"
#include "Passenger.h"

using namespace std;

class FlightAttendant : public Employee {
public:
    FlightAttendant(const string& name, const string& surname, time_t birthDate, 
        const ContactInfo& data, double salary, bool isAvailable, 
        int serviceYears, const vector<string>& languages);

    void setServiceYears(int years);
    void setLanguages(const vector<string>& languages);

    int getServiceYears() const;
    const vector<string>& getLanguages() const;

    void addLanguage(const string& language);

private:
    int serviceYears_;
    vector<string> languages_;
};
