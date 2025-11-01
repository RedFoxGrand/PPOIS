#include "CheckIn.h"

CheckIn::CheckIn(const string& checkInId, const Passenger& passenger, 
    const Flight& flight, CheckInStatus status) : 
    checkInId_(checkInId), 
    passenger_(passenger), 
    flight_(flight), 
    status_(status) {
}

void CheckIn::setCheckInId(const string& checkInId) { 
    checkInId_ = checkInId; 
}
void CheckIn::setPassenger(const Passenger& passenger) { 
    passenger_ = passenger; 
}
void CheckIn::setFlight(const Flight& flight) { 
    flight_ = flight; 
}
void CheckIn::setStatus(CheckInStatus status) { 
    status_ = status; 
}

const string& CheckIn::getCheckInId() const { 
    return checkInId_; 
}
const Passenger& CheckIn::getPassenger() const { 
    return passenger_; 
}
const Flight& CheckIn::getFlight() const { 
    return flight_; 
}
CheckInStatus CheckIn::getStatus() const { 
    return status_; 
}

void CheckIn::perform() {
    status_ = CheckInStatus::InProgress;

    if (!flight_.getAircraft().getIsAvailable()) {
        status_ = CheckInStatus::Failed;
        return;
    }

    status_ = CheckInStatus::Completed;
}

void CheckIn::issueBoardingPass() {
    if (status_ != CheckInStatus::Completed) throw InvalidStatusException("Регистрация уже завершена");

    status_ = CheckInStatus::Closed;
}
