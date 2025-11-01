#include "LoyaltyProgram.h"
#include <iomanip>

LoyaltyProgram::LoyaltyProgram(const string& programId, const Passenger& member,
    int miles, TierType type, time_t joinDate) : 
    programId_(programId),
    member_(member),
    miles_(miles),
    type_(type),
    joinDate_(joinDate) {
}

void LoyaltyProgram::setProgramId(const string& programId) {
    programId_ = programId;
}
void LoyaltyProgram::setMember(const Passenger& member) {
    member_ = member; 
}
void LoyaltyProgram::setMiles(int miles) {
    miles_ = miles; 
}
void LoyaltyProgram::setTierType(TierType type) {
    type_ = type; 
}
void LoyaltyProgram::setJoinDate(time_t joinDate) { 
    joinDate_ = joinDate; 
}

const string& LoyaltyProgram::getProgramId() const {
    return programId_;
}
const Passenger& LoyaltyProgram::getMember() const {
    return member_; 
}
int LoyaltyProgram::getMiles() const {
    return miles_; 
}
TierType LoyaltyProgram::getTierType() const {
    return type_; 
}
time_t LoyaltyProgram::getJoinDate() const {
    return joinDate_; 
}

void LoyaltyProgram::addMiles(int amount) {
    if (amount > 0) miles_ += amount;
    else return;
}

bool LoyaltyProgram::redeemMiles(int amount) {
    if (amount <= 0) return false;
    if (amount > miles_) return false;
    miles_ -= amount;

    return true;
}

void LoyaltyProgram::upgradeTier(TierType newTier) {
    if (static_cast<int>(newTier) > static_cast<int>(type_)) type_ = newTier;
    else return;
}
