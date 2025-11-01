#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <exception>

using namespace std;

class App {
public:
    App(const string& name, const string& version, const string& launchDate, const bool isRunning);

    void setName(const string& name);
    void setVersion(const string& version);
    void setLaunchDate(const string& launchDate);
    void setIsRunning(const bool isRunning);

    const string& getName() const;
    const string& getVersion() const;
    const string& getLaunchDate() const;
    const bool getIsRunning() const;

    void start();
    void shutdown();
    void checkForUpdates(const string& version);

private:
    string name_;
    string version_;
    string launchDate_;
    bool isRunning_;
};
