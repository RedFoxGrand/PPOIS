#pragma once
#include "User.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Ban {
public:
    Ban(const string& reason, const string& startDate, const string& endDate, const User& bannedUser);
    Ban(const string& reason, const User& bannedUser);

    void setReason(const string& reason);
    void setStartDate(const string& startDate);
    void setEndDate(const string& endDate);
    void setBannedUser(const User& bannedUser);

    const string& getReason() const;
    const string& getStartDate() const;
    const string& getEndDate() const;
    const User& getBannedUser() const;

    bool isActive() const;
    void liftBan();

private:
    string reason_;
    string startDate_;
    string endDate_;
    User bannedUser_;
};
