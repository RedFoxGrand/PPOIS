#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Person.h"
#include "Passport.h"
#include "Flight.h"

using namespace std;

class Passenger : public Person {
public:
    Passenger(const string& name, const string& surname, time_t birthDate,
        const ContactInfo& data, const string& passengerId, const Passport& passport);

    void setPassengerId(const string& passengerId);
    void setPassport(const Passport& passport);
    void setTicketNumbers(const vector<string>& ticketNumbers);

    const string& getPassengerId() const;
    const Passport& getPassport() const;
    const vector<string>& getTicketNumbers() const;

    void addTicket(const string& ticketNumber);
    void redeemMiles(int miles);

private:
    string passengerId_;
    Passport passport_;
    vector<string> ticketNumbers_;
};
