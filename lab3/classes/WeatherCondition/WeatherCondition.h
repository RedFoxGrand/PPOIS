#pragma once
#include <iostream>
#include <string>

using namespace std;

class WeatherCondition {
public:
    WeatherCondition(const string& location, const string& condition,
        const string& alertLevel, double temperature, double windSpeed);

    void setLocation(const string& location);
    void setCondition(const string& condition);
    void setAlertLevel(const string& alertLevel);
    void setTemperature(double temperature);
    void setWindSpeed(double windSpeed);

    const string& getLocation() const;
    const string& getCondition() const;
    const string& getAlertLevel() const;
    double getTemperature() const;
    double getWindSpeed() const;

    bool isSafeForFlight() const;
    void update(const string& newCondition);
    void getForecast() const;
    string triggerAlert(const string& reason);

private:
    string location_;
    string condition_;
    string alertLevel_;
    double temperature_;
    double windSpeed_;
};
