#pragma once
#include <iostream>
#include <string>
#include "Passenger.h"
#include "Flight.h"
#include "InvalidStatusException.h"

using namespace std;

enum class CheckInStatus { NotStarted, InProgress, Completed, Failed, Closed };

class CheckIn {
public:
    CheckIn(const string& checkInId, const Passenger& passenger, 
        const Flight& flight, CheckInStatus status);

    void setCheckInId(const string& checkInId);
    void setPassenger(const Passenger& passenger);
    void setFlight(const Flight& flight);
    void setStatus(CheckInStatus status);

    const string& getCheckInId() const;
    const Passenger& getPassenger() const;
    const Flight& getFlight() const;
    CheckInStatus getStatus() const;

    void perform();
    void issueBoardingPass();

private:
    string checkInId_;
    Passenger passenger_;
    Flight flight_;
    CheckInStatus status_;
};
