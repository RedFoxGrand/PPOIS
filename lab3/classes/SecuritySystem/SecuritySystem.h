#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "SecurityOfficer.h"

using namespace std;

class SecuritySystem {
public:
    SecuritySystem(int activeCameras, const string& accessLogs, 
        const string& alerts, const vector<SecurityOfficer>& officers);

    void setActiveCameras(int activeCameras);
    void setAccessLogs(const string& accessLogs);
    void setAlerts(const string& alerts);
    void setOfficers(const vector<SecurityOfficer>& officers);

    int getActiveCameras() const;
    const string& getAccessLogs() const;
    const string& getAlerts() const;
    const vector<SecurityOfficer>& getOfficers() const;

    void alert(const string& message);
    void flagSuspiciousActivity(const string& description);

private:
    int activeCameras_;
    string accessLogs_;
    string alerts_;
    vector<SecurityOfficer> officers_;
};
