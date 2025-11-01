#pragma once
#include <iostream>
#include <string>

using namespace std;

enum class SeatClassType { Economy, Premium, Business };

class Seat {
public:
    Seat(const string& seatNumber, bool isOccupied, bool isAvailable, SeatClassType type);

    void setSeatNumber(const string& seatNumber);
    void setOccupied(bool occupied);
    void setAvailable(bool available);
    void setType(SeatClassType type);

    const string& getSeatNumber() const;
    bool isOccupiedStatus() const;
    bool isAvailableStatus() const;
    SeatClassType getType() const;

    void reserve();
    void release();

private:
    string seatNumber_;
    bool isOccupied_;
    bool isAvailable_;
    SeatClassType type_;
};
