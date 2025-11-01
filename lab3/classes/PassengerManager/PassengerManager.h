#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Passenger.h"
#include "PassengerNotFound.h"
#include "PassengerHistoryNotFound.h"

using namespace std;

class PassengerManager {
public:
    PassengerManager(const vector<Passenger>& passengers);

    void setPassengers(const vector<Passenger>& passengers);

    const vector<Passenger>& getPassengers() const;

    void registerPassenger(const Person& person);
    Passenger findByPassport(const Passport& passport);
    Passenger getPassengerHistory(const string& passportNumber);

private:
    vector<Passenger> passengers_;
};
