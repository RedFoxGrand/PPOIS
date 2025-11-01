#include "PassengerManager.h"
#include <ctime>
#include <iostream>

using namespace std;

PassengerManager::PassengerManager(const vector<Passenger>& passengers) : 
    passengers_(passengers) {
}

void PassengerManager::setPassengers(const vector<Passenger>& passengers) {
    passengers_ = passengers;
}

const vector<Passenger>& PassengerManager::getPassengers() const {
    return passengers_;
}

void PassengerManager::registerPassenger(const Person& person) {

    time_t now = time(nullptr);
    Visa emptyVisa("V0000", "Отсутствует", now, now, VisaType::Tourist);
    Passport defaultPassport("TEMP" + to_string(passengers_.size() + 1),
        "Неизвестно", person.getFullName(), now, now + 31536000, emptyVisa, MaritalStatus::NotMarried);

    Passenger newPassenger(person.getName(), person.getSurname(), person.getBirthDate(), person.getContactInfo(),
        "PID" + to_string(passengers_.size() + 1), defaultPassport);

    passengers_.push_back(newPassenger);
}

Passenger PassengerManager::findByPassport(const Passport& passport) {
    for (const auto& passenger : passengers_) {
        if (passenger.getPassport().getPassportNumber() == passport.getPassportNumber()) return passenger;
    }

    throw PassengerNotFound("Пассажир не найден");
}

Passenger PassengerManager::getPassengerHistory(const string& passportNumber) {
    for (const auto& passenger : passengers_) {
        if (passenger.getPassport().getPassportNumber() == passportNumber) {
            return passenger;
        }
    }
    throw PassengerHistoryNotFound("История пассажира не найдена");
}
