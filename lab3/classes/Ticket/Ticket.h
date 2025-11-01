#pragma once
#include <iostream>
#include <string>
#include "Passenger.h"
#include "Seat.h"
#include "Fare.h"

using namespace std;

class Ticket {
public:
    Ticket(const string& ticketNumber, const Passenger& passenger,
        const string& passengerId, const Flight& flight,
        const string& flightNumber, const Seat& seat, const Fare& fare);

    void setTicketNumber(const string& ticketNumber);
    void setPassenger(const Passenger& passenger);
    void setPassengerId(const string& passengerId);
    void setFlight(const Flight& flight);
    void setFlightNumber(const string& flightNumber);
    void setSeat(const Seat& seat);
    void setFare(const Fare& fare);

    const string& getTicketNumber() const;
    const Passenger& getPassenger() const;
    const string& getPassengerId() const;
    const Flight& getFlight() const;
    const string& getFlightNumber() const;
    const Seat& getSeat() const;
    const Fare& getFare() const;

    void changeSeat(const Seat& newSeat);

private:
    string ticketNumber_;
    Passenger passenger_;
    string passengerId_;
    Flight flight_;
    string flightNumber_;
    Seat seat_;
    Fare fare_;
};
