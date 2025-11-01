#include "LostAndFound.h"

LostAndFound::LostAndFound(const string& reportID, const string& locationFound, 
    LostAndFoundStatus status, const vector<Baggage>& lostItems, const vector<Baggage>& foundItems) : 
    reportID_(reportID), 
    locationFound_(locationFound), 
    status_(status), 
    lostItems_(lostItems), 
    foundItems_(foundItems){
}

void LostAndFound::setReportID(const string& reportID) { 
    reportID_ = reportID; 
}
void LostAndFound::setLocationFound(const string& locationFound) { 
    locationFound_ = locationFound; 
}
void LostAndFound::setStatus(LostAndFoundStatus status) { 
    status_ = status; 
}
void LostAndFound::setlostItems(const vector<Baggage>& lostItems) { 
    lostItems_ = lostItems; 
}
void LostAndFound::setFoundItems(const vector<Baggage>& foundItems) { 
    foundItems_ = foundItems; 
}

const string& LostAndFound::getReportID() const { 
    return reportID_;
}
const string& LostAndFound::getLocationFound() const {
    return locationFound_; 
}
LostAndFoundStatus LostAndFound::getStatus() const {
    return status_; 
}
const vector<Baggage>& LostAndFound::getLostItems() const {
    return lostItems_; 
}
const vector<Baggage>& LostAndFound::getFoundItems() const {
    return foundItems_;
}

void LostAndFound::reportLost(const Baggage& baggage) {
    lostItems_.push_back(baggage);
    status_ = LostAndFoundStatus::Reported;
}

void LostAndFound::reportFound(const Baggage& baggage) {
    foundItems_.push_back(baggage);
    status_ = LostAndFoundStatus::Located;
}

void LostAndFound::claimItem(const Passenger& passenger) {
    for (auto it = foundItems_.begin(); it != foundItems_.end(); ++it) {
        if (it->getOwner().getFullName() == passenger.getFullName()) {;
            foundItems_.erase(it);
            status_ = LostAndFoundStatus::Claimed;
            return;
        }
    }
}

