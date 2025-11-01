#include "BookingManager.h"

BookingManager::BookingManager(const vector<Booking>& bookings) : 
    bookings_(bookings) {
}

void BookingManager::setBookings(const vector<Booking>& bookings) {
    bookings_ = bookings;
}

const vector<Booking>& BookingManager::getBookings() const {
    return bookings_;
}

Booking* BookingManager::findByPassenger(const string& passengerId) {
    for (auto& booking : bookings_) {
        if (booking.getPassenger().getPassengerId() == passengerId) return &booking;
    }
    return nullptr;
}

Booking* BookingManager::modifyBooking(const string& bookingId) {
    for (auto& booking : bookings_) {
        if (booking.getBookingId() == bookingId) {
            booking.setStatus(BookingStatus::Confirmed);
            return &booking;
        }
    }

    return nullptr;
}