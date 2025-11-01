#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "Passenger.h"

using namespace std;

enum class TierType { Silver, Gold, Platinum };

class LoyaltyProgram {
public:
    LoyaltyProgram(const string& programId, const Passenger& member,
        int miles, TierType type, time_t joinDate);

    void setProgramId(const string& programId);
    void setMember(const Passenger& member);
    void setMiles(int miles);
    void setTierType(TierType type);
    void setJoinDate(time_t joinDate);

    const string& getProgramId() const;
    const Passenger& getMember() const;
    int getMiles() const;
    TierType getTierType() const;
    time_t getJoinDate() const;

    void addMiles(int amount);
    bool redeemMiles(int amount);
    void upgradeTier(TierType newTier);

private:
    string programId_;
    Passenger member_;
    int miles_;
    TierType type_;
    time_t joinDate_;
};
