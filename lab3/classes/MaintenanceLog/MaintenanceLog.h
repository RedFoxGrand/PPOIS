#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "Aircraft.h"

using namespace std;

class MaintenanceLog {
public:
    MaintenanceLog(const string& recordId, const Aircraft& aircraft, 
        const string& description, time_t date);

    void setRecordId(const string& recordId);
    void setAircraft(const Aircraft& aircraft);
    void setDescription(const string& description);
    void setDate(time_t date);

    const string& getRecordId() const;
    const Aircraft& getAircraft() const;
    const string& getDescription() const;
    time_t getDate() const;

    void addEntry(const string& text);
    void printLog() const;

private:
    string recordId_;
    Aircraft aircraft_;
    string description_;
    time_t date_;
};
