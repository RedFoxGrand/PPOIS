#include "Booking.h"

Booking::Booking(const string& bookingId, const Passenger& passenger, const Flight& flight,
    bool isPaid, const vector<Ticket>& tickets, BookingStatus status) : 
    bookingId_(bookingId),
    passenger_(passenger),
    flight_(flight),
    isPaid_(isPaid),
    tickets_(tickets),
    status_(status) {
}

void Booking::setBookingId(const string& bookingId) { 
    bookingId_ = bookingId; 
}
void Booking::setPassenger(const Passenger& passenger) { 
    passenger_ = passenger; 
}
void Booking::setFlight(const Flight& flight) { 
    flight_ = flight; 
}
void Booking::setPaid(bool paid) { 
    isPaid_ = paid; 
}
void Booking::setTickets(const vector<Ticket>& tickets) { 
    tickets_ = tickets; 
}
void Booking::setStatus(BookingStatus status) { 
    status_ = status; 
}

const string& Booking::getBookingId() const { 
    return bookingId_; 
}
const Passenger& Booking::getPassenger() const { 
    return passenger_; 
}
const Flight& Booking::getFlight() const { 
    return flight_; 
}
bool Booking::isPaidStatus() const { 
    return isPaid_; 
}
const vector<Ticket>& Booking::getTickets() const { 
    return tickets_; 
}
BookingStatus Booking::getStatus() const { 
    return status_; 
}

void Booking::confirmPayment(Account& account, double amount) {
    if (account.deductFunds(amount)) {
        isPaid_ = true;
        status_ = BookingStatus::Confirmed;
    }
    else status_ = BookingStatus::Pending;
}

void Booking::cancel() {
    if (status_ == BookingStatus::Cancelled) throw InvalidStatusException("Бронирование уже отменено");

    status_ = BookingStatus::Cancelled;
}

