#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "Aircraft.h"
#include "MaintenanceLog.h"

using namespace std;

class AircraftMaintenanceSystem {
public:
    AircraftMaintenanceSystem(const vector<Aircraft>& aircrafts, const vector<MaintenanceLog>& logs);

    void setAircrafts(const vector<Aircraft>& aircrafts);
    void setLogs(const vector<MaintenanceLog>& logs);

    const vector<Aircraft>& getAircrafts() const;
    const vector<MaintenanceLog>& getLogs() const;

    void recordMaintenance(const Aircraft& aircraft);
    void scheduleCheck(Aircraft& aircraft);
    vector<MaintenanceLog> getMaintenanceHistory(const Aircraft& aircraft) const;

private:
    vector<MaintenanceLog> logs_;
    vector<Aircraft> aircrafts_;
};
