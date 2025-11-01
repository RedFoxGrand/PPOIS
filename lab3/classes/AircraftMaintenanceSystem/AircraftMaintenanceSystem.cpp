#include "AircraftMaintenanceSystem.h"


AircraftMaintenanceSystem::AircraftMaintenanceSystem(const vector<Aircraft>& aircrafts, 
    const vector<MaintenanceLog>& logs) : 
    aircrafts_(aircrafts), logs_(logs) {
}

void AircraftMaintenanceSystem::setAircrafts(const vector<Aircraft>& aircrafts) {
    aircrafts_ = aircrafts;
}
void AircraftMaintenanceSystem::setLogs(const vector<MaintenanceLog>& logs) {
    logs_ = logs;
}

const vector<Aircraft>& AircraftMaintenanceSystem::getAircrafts() const {
    return aircrafts_;
}
const vector<MaintenanceLog>& AircraftMaintenanceSystem::getLogs() const {
    return logs_;
}

void AircraftMaintenanceSystem::recordMaintenance(const Aircraft& aircraft) {
    string recordId = "ML-" + aircraft.getTailNumber() + "-" + to_string(logs_.size() + 1);
    string desc = "Плановая проверка технического обслуживания завершена";
    time_t now = time(nullptr);

    MaintenanceLog log(recordId, aircraft, desc, now);
    logs_.push_back(log);
}

void AircraftMaintenanceSystem::scheduleCheck(Aircraft& aircraft) {
    aircraft.setStatus(AircraftStatus::UnderMaintenance);
    aircraft.setIsAvailable(false);
    recordMaintenance(aircraft);
}

vector<MaintenanceLog> AircraftMaintenanceSystem::getMaintenanceHistory(const Aircraft& aircraft) const {
    vector<MaintenanceLog> history;
    for (const auto& log : logs_) {
        if (log.getAircraft().getTailNumber() == aircraft.getTailNumber()) history.push_back(log);
    }
    return history;
}
