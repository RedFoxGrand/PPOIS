#include "WeatherCondition.h"

WeatherCondition::WeatherCondition(const string& location, const string& condition,
    const string& alertLevel, double temperature, double windSpeed) : 
    location_(location),
    condition_(condition),
    alertLevel_(alertLevel),
    temperature_(temperature),
    windSpeed_(windSpeed) {
}

void WeatherCondition::setLocation(const string& location) {
    location_ = location;
}
void WeatherCondition::setCondition(const string& condition) { 
    condition_ = condition; 
}
void WeatherCondition::setAlertLevel(const string& alertLevel) {
    alertLevel_ = alertLevel;
}
void WeatherCondition::setTemperature(double temperature) {
    temperature_ = temperature; 
}
void WeatherCondition::setWindSpeed(double windSpeed) { 
    windSpeed_ = windSpeed; 
}

const string& WeatherCondition::getLocation() const {
    return location_; 
}
const string& WeatherCondition::getCondition() const { 
    return condition_; 
}
const string& WeatherCondition::getAlertLevel() const { 
    return alertLevel_;
}
double WeatherCondition::getTemperature() const { 
    return temperature_;
}
double WeatherCondition::getWindSpeed() const {
    return windSpeed_;
}

bool WeatherCondition::isSafeForFlight() const {
    if (windSpeed_ > 60.0 || condition_ == "Шторм" || condition_ == "Гром" || alertLevel_ == "Высокий") return false;
    return true;
}

void WeatherCondition::update(const string& newCondition) {
    condition_ = newCondition;
}

void WeatherCondition::getForecast() const {
    cout << "Прогноз погоды для " << location_ << ":\n"
        << "   Состояние: " << condition_ << "\n"
        << "   Температура: " << temperature_ << "°C\n"
        << "   Скорость ветра: " << windSpeed_ << " км/ч\n"
        << "   Уровень оповещения: " << alertLevel_ << endl;
}

string WeatherCondition::triggerAlert(const string& reason) {
    alertLevel_ = "Высокий";
    return "Сработало предупреждение о погоде " + location_ + "! Причина: " + reason;
}

