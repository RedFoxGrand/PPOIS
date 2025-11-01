#include "Passenger.h"

Passenger::Passenger(const string& name, const string& surname, time_t birthDate,
    const ContactInfo& data, const string& passengerId, const Passport& passport) : 
    Person(name, surname, birthDate, data),
    passengerId_(passengerId),
    passport_(passport) {
}

void Passenger::setPassengerId(const string& passengerId) { 
    passengerId_ = passengerId; 
}
void Passenger::setPassport(const Passport& passport) { 
    passport_ = passport;
}
void Passenger::setTicketNumbers(const vector<string>& ticketNumbers) { 
    ticketNumbers_ = ticketNumbers;
}

const string& Passenger::getPassengerId() const { 
    return passengerId_; 
}
const Passport& Passenger::getPassport() const { 
    return passport_; 
}
const vector<string>& Passenger::getTicketNumbers() const { 
    return ticketNumbers_; 
}

void Passenger::addTicket(const string& ticketNumber) {
    ticketNumbers_.push_back(ticketNumber);
}