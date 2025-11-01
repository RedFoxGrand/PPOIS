#pragma once
#include "SubscriptionExpiredException.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Subscription {
public:
    Subscription(const string& planName, const string& startDate, const string& endDate,
        double monthlyCost, bool isActive, bool autoRenew);

    void setPlanName(const string& planName);
    void setStartDate(const string& startDate);
    void setEndDate(const string& endDate);
    void setMonthlyCost(double monthlyCost);
    void setIsActive(bool isActive);
    void setAutoRenew(bool autoRenew);

    const string& getPlanName() const;
    const string& getStartDate() const;
    const string& getEndDate() const;
    double getMonthlyCost() const;
    bool getIsActive() const;
    bool getAutoRenew() const;

    void renewSubscription(string newEndDate);
    bool isExpired() const;

private:
    double monthlyCost_;
    string planName_;
    string startDate_;
    string endDate_;
    bool isActive_;
    bool autoRenew_;
};
