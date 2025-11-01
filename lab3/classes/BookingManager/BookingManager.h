#pragma once
#include <iostream>
#include <vector>
#include "Booking.h"
#include "EmptyObjectException.h"

using namespace std;

class BookingManager {
public:
    BookingManager() = default;
    BookingManager(const vector<Booking>& bookings);

    void setBookings(const vector<Booking>& bookings);
    const vector<Booking>& getBookings() const;

    Booking* findByPassenger(const string& passengerId);
    Booking* modifyBooking(const string& bookingId);

private:
    vector<Booking> bookings_;
};
