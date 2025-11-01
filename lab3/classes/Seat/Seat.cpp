#include "Seat.h"

Seat::Seat(const string& seatNumber, bool isOccupied, bool isAvailable, SeatClassType type) : 
    seatNumber_(seatNumber),
    isOccupied_(isOccupied),
    isAvailable_(isAvailable),
    type_(type) {
}

void Seat::setSeatNumber(const string& seatNumber) { 
    seatNumber_ = seatNumber; 
}
void Seat::setOccupied(bool occupied) {
    isOccupied_ = occupied; 
}
void Seat::setAvailable(bool available) {
    isAvailable_ = available; 
}
void Seat::setType(SeatClassType type) {
    type_ = type; 
}

const string& Seat::getSeatNumber() const {
    return seatNumber_; 
}
bool Seat::isOccupiedStatus() const {
    return isOccupied_;
}
bool Seat::isAvailableStatus() const {
    return isAvailable_; 
}
SeatClassType Seat::getType() const {
    return type_; 
}

void Seat::reserve() {
    if (!isAvailable_) return;
    isOccupied_ = true;
    isAvailable_ = false;
}

void Seat::release() {
    if (!isOccupied_) return;
    isOccupied_ = false;
    isAvailable_ = true;
}

