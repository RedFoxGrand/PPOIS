#include "App.h"

App::App(const string& name, const string& version, const string& launchDate, const bool isRunning) :
    name_(name),
    version_(version),
    launchDate_(launchDate),
    isRunning_(isRunning) {
}

void App::setName(const string& name) {
    name_ = name;
}
void App::setVersion(const string& version) {
    version_ = version;
}
void App::setLaunchDate(const string& launchDate) {
    launchDate_ = launchDate;
}
void App::setIsRunning(const bool isRunning) {
    isRunning_ = isRunning;
}


const string& App::getName() const {
    return name_;
}
const string& App::getVersion() const {
    return version_;
}
const string& App::getLaunchDate() const {
    return launchDate_;
}
const bool App::getIsRunning() const {
    return isRunning_;
}

void App::start()
{
    if (isRunning_) return;

    isRunning_ = true;

    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);

    tm timeInfo;
    localtime_s(&timeInfo, &time);

    stringstream ss;
    ss << put_time(&timeInfo, "%d.%m.%Y %H:%M:%S");
    launchDate_ = ss.str();
}

void App::shutdown() {
    if (!isRunning_) return;

    isRunning_ = false;
}

void App::checkForUpdates(const string& version) {
    if (version.empty()) return;
    if (version_ == version) return;

    version_ = version;
}
