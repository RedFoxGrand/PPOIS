#pragma once
#include <iostream>
#include <string>
#include "AircraftModel.h"
#include "Schedule.h"
#include "InvalidFuelException.h"

using namespace std;

enum class AircraftStatus { Available, InFlight, UnderMaintenance, Grounded, ScheduledForFlight };

class Flight;

class Aircraft {
public:
    Aircraft(const string& tailNumber, const AircraftModel& model,
        int fuelLevel, AircraftStatus status, bool isAvailable);

    void setTailNumber(const string& tailNumber);
    void setModel(const AircraftModel& model);
    void setFuelLevel(int fuelLevel);
    void setStatus(AircraftStatus status);
    void setIsAvailable(bool available);

    const string& getTailNumber() const;
    const AircraftModel& getModel() const;
    int getFuelLevel() const;
    AircraftStatus getStatus() const;
    bool getIsAvailable() const;

    void refuel(int liters);
    void assignFlight(const Flight& flight);
    Schedule scheduleMaintenance();

private:
    string tailNumber_;
    AircraftModel model_;
    int fuelLevel_;
    AircraftStatus status_;
    bool isAvailable_;
};
