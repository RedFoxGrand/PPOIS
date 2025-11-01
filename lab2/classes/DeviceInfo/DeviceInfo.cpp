#include "DeviceInfo.h"
#include <regex>
#include <ctime>

DeviceInfo::DeviceInfo(const string& userId, const string& deviceId, const string& os,
    const string& ipAddress, const string& lastActive, DeviceType deviceType) :
    userId_(userId),
    deviceId_(deviceId),
    os_(os),
    ipAddress_(ipAddress),
    lastActive_(lastActive),
    deviceType_(deviceType) {
}

void DeviceInfo::setUserId(const string& userId) {
    userId_ = userId;
}
void DeviceInfo::setDeviceId(const string& deviceId) {
    deviceId_ = deviceId;
}
void DeviceInfo::setOs(const string& os) {
    os_ = os;
}
void DeviceInfo::setIpAddress(const string& ipAddress) {
    ipAddress_ = ipAddress;
}
void DeviceInfo::setLastActive(const string& lastActive) {
    lastActive_ = lastActive;
}
void DeviceInfo::setDeviceType(DeviceType deviceType) {
    deviceType_ = deviceType;
}

const string& DeviceInfo::getUserId() const {
    return userId_;
}
const string& DeviceInfo::getDeviceId() const {
    return deviceId_;
}
const string& DeviceInfo::getOs() const {
    return os_;
}
const string& DeviceInfo::getIpAddress() const {
    return ipAddress_;
}
const string& DeviceInfo::getLastActive() const {
    return lastActive_;
}
DeviceType DeviceInfo::getDeviceType() const {
    return deviceType_;
}

void DeviceInfo::detectDeviceType() {
    if (os_.empty()) {
        cout << "Строка ОС пуста." << endl;
        return ;
    }

    if (os_.find("iPad") != string::npos || os_.find("Tablet") != string::npos) {
        deviceType_ = DeviceType::TABLET;
    }
    else if (os_.find("Android") != string::npos || os_.find("iOS") != string::npos) {
        deviceType_ = DeviceType::MOBILE;
    }
    else if (os_.find("Windows") != string::npos || os_.find("Linux") != string::npos || os_.find("macOS") != string::npos) {
        deviceType_ = DeviceType::DESKTOP;
    }
    else {
        cout << "Тип устройства не определён по ОС: " << os_ << endl;
        return;
    }

    switch (deviceType_) {
    case DeviceType::MOBILE: cout << "Мобильное"; break;
    case DeviceType::DESKTOP: cout << "Десктоп"; break;
    case DeviceType::TABLET: cout << "Планшет"; break;
    default: cout << "Неизвестный"; break;
    }
    cout << endl;
}

void DeviceInfo::updateLastActive() {
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);

    tm timeInfo;
    localtime_s(&timeInfo, &time);

    stringstream ss;
    ss << put_time(&timeInfo, "%d.%m.%Y %H:%M:%S");
    lastActive_ = ss.str();

    lastActive_.erase(remove(lastActive_.begin(), lastActive_.end(), '\n'), lastActive_.end());
}

void DeviceInfo::validateIPAddress() {
    if (ipAddress_.empty()) return;

    regex ipv4Pattern(R"(^((25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)\.){3}(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)$)");

    if (regex_match(ipAddress_, ipv4Pattern)) return;

    return;
}
