#include "SecuritySystem.h"

SecuritySystem::SecuritySystem(int activeCameras, const string& accessLogs, 
    const string& alerts, const vector<SecurityOfficer>& officers) : 
    activeCameras_(activeCameras), 
    accessLogs_(accessLogs), 
    alerts_(alerts), 
    officers_(officers) {
}

void SecuritySystem::setActiveCameras(int activeCameras) {
    activeCameras_ = activeCameras;
}
void SecuritySystem::setAccessLogs(const string& accessLogs) { 
    accessLogs_ = accessLogs; 
}
void SecuritySystem::setAlerts(const string& alerts) {
    alerts_ = alerts;
}
void SecuritySystem::setOfficers(const vector<SecurityOfficer>& officers) {
    officers_ = officers; 
}

int SecuritySystem::getActiveCameras() const {
    return activeCameras_; 
}
const string& SecuritySystem::getAccessLogs() const {
    return accessLogs_; 
}
const string& SecuritySystem::getAlerts() const {
    return alerts_; 
}
const vector<SecurityOfficer>& SecuritySystem::getOfficers() const { 
    return officers_; 
}

void SecuritySystem::alert(const string& message) {
    time_t now = time(nullptr);
    string timeStr = ctime(&now);
    timeStr.pop_back();

    cout << message << " [" << timeStr << "]" << endl;
    alerts_ += "[" + timeStr + "] " + message + "\n";
}

void SecuritySystem::flagSuspiciousActivity(const string& description) {
    time_t now = time(nullptr);
    string timeStr = ctime(&now);
    timeStr.pop_back();

    cout << description << " [" << timeStr << "]" << endl;
    alerts_ += "[" + timeStr + "] " + description + "\n";
}

