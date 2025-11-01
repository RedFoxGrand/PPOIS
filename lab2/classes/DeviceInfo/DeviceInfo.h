#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <exception>

using namespace std;

enum class DeviceType { MOBILE, DESKTOP, TABLET };

class DeviceInfo {
public:
    DeviceInfo(const string& userId, const string& deviceId, const string& os,
               const string& ipAddress, const string& lastActive, DeviceType deviceType);

    void setUserId(const string& userId);
    void setDeviceId(const string& deviceId);
    void setOs(const string& os);
    void setIpAddress(const string& ipAddress);
    void setLastActive(const string& lastActive);
    void setDeviceType(DeviceType deviceType);

    const string& getUserId() const;
    const string& getDeviceId() const;
    const string& getOs() const;
    const string& getIpAddress() const;
    const string& getLastActive() const;
    DeviceType getDeviceType() const;

    void detectDeviceType();
    void updateLastActive();
    void validateIPAddress();

private:
    string userId_;
    string deviceId_;
    string os_;
    string ipAddress_;
    string lastActive_;
    DeviceType deviceType_;
};
