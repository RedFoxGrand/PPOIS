#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Passenger.h"
#include "Ticket.h"
#include "Account.h"
#include "InvalidStatusException.h"

using namespace std;

enum class BookingStatus { Pending, Confirmed, Cancelled, CheckedIn, NoShow, Refunded };

class Booking {
public:
    Booking(const string& bookingId, const Passenger& passenger, const Flight& flight,
        bool isPaid, const vector<Ticket>& tickets, BookingStatus status);

    void setBookingId(const string& bookingId);
    void setPassenger(const Passenger& passenger);
    void setFlight(const Flight& flight);
    void setPaid(bool paid);
    void setTickets(const vector<Ticket>& tickets);
    void setStatus(BookingStatus status);

    const string& getBookingId() const;
    const Passenger& getPassenger() const;
    const Flight& getFlight() const;
    bool isPaidStatus() const;
    const vector<Ticket>& getTickets() const;
    BookingStatus getStatus() const;

    void confirmPayment(Account& account, double amount);
    void cancel();

private:
    string bookingId_;
    Passenger passenger_;
    Flight flight_;
    bool isPaid_;
    vector<Ticket> tickets_;
    BookingStatus status_;
};
