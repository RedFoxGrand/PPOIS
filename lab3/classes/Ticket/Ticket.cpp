#include "Ticket.h"

Ticket::Ticket(const string& ticketNumber, const Passenger& passenger,
    const string& passengerId, const Flight& flight,
    const string& flightNumber, const Seat& seat, const Fare& fare) : 
    ticketNumber_(ticketNumber),
    passenger_(passenger),
    passengerId_(passengerId),
    flight_(flight),
    flightNumber_(flightNumber),
    seat_(seat),
    fare_(fare) {
}

void Ticket::setTicketNumber(const string& ticketNumber) { 
    ticketNumber_ = ticketNumber; 
}
void Ticket::setPassenger(const Passenger& passenger) { 
    passenger_ = passenger;
}
void Ticket::setPassengerId(const string& passengerId) {
    passengerId_ = passengerId; 
}
void Ticket::setFlight(const Flight& flight) {
    flight_ = flight;
}
void Ticket::setFlightNumber(const string& flightNumber) {
    flightNumber_ = flightNumber; 
}
void Ticket::setSeat(const Seat& seat) {
    seat_ = seat;
}
void Ticket::setFare(const Fare& fare) {
    fare_ = fare;
}

const string& Ticket::getTicketNumber() const {
    return ticketNumber_; 
}
const Passenger& Ticket::getPassenger() const {
    return passenger_;
}
const string& Ticket::getPassengerId() const {
    return passengerId_; 
}
const Flight& Ticket::getFlight() const {
    return flight_; 
}
const string& Ticket::getFlightNumber() const { 
    return flightNumber_; 
}
const Seat& Ticket::getSeat() const { 
    return seat_; 
}
const Fare& Ticket::getFare() const {
    return fare_;
}

void Ticket::changeSeat(const Seat& newSeat) {
    seat_ = newSeat;
}

