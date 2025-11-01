#include "Ban.h"

Ban::Ban(const string& reason, const string& startDate, const string& endDate, const User& bannedUser) :
    reason_(reason),
    startDate_(startDate),
    endDate_(endDate),
    bannedUser_(bannedUser) {
}

Ban::Ban(const string& reason, const User& bannedUser) :
    reason_(reason),
    startDate_("now"),
    endDate_("0"),
    bannedUser_(bannedUser) {
}

void Ban::setReason(const string& reason) {
    reason_ = reason;
}
void Ban::setStartDate(const string& startDate) {
    startDate_ = startDate;
}
void Ban::setEndDate(const string& endDate) {
    endDate_ = endDate;
}
void Ban::setBannedUser(const User& bannedUser) {
    bannedUser_ = bannedUser;
}

const string& Ban::getReason() const {
    return reason_;
}
const string& Ban::getStartDate() const {
    return startDate_;
}
const string& Ban::getEndDate() const {
    return endDate_;
}
const User& Ban::getBannedUser() const {
    return bannedUser_;
}

bool Ban::isActive() const {
    return endDate_ == "0";
}

void Ban::liftBan() {
    if (!isActive()) return;

    endDate_ = "0";
}
