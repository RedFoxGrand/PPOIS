#include "Subscription.h"

Subscription::Subscription(const string& planName, const string& startDate, const string& endDate,
    double monthlyCost, bool isActive, bool autoRenew) :
    planName_(planName),
    startDate_(startDate),
    endDate_(endDate),
    monthlyCost_(monthlyCost),
    isActive_(isActive),
    autoRenew_(autoRenew) {
}

void Subscription::setPlanName(const string& planName) {
    planName_ = planName;
}
void Subscription::setStartDate(const string& startDate) {
    startDate_ = startDate;
}
void Subscription::setEndDate(const string& endDate) {
    endDate_ = endDate;
}
void Subscription::setMonthlyCost(double monthlyCost) {
    monthlyCost_ = monthlyCost;
}
void Subscription::setIsActive(bool isActive) {
    isActive_ = isActive;
}
void Subscription::setAutoRenew(bool autoRenew) {
    autoRenew_ = autoRenew;
}

const string& Subscription::getPlanName() const {
    return planName_;
}
const string& Subscription::getStartDate() const {
    return startDate_;
}
const string& Subscription::getEndDate() const {
    return endDate_;
}
double Subscription::getMonthlyCost() const {
    return monthlyCost_;
}
bool Subscription::getIsActive() const {
    return isActive_;
}
bool Subscription::getAutoRenew() const {
    return autoRenew_;
}

void Subscription::renewSubscription(string newEndDate) {
    if (autoRenew_ && isActive_) endDate_ = newEndDate;
    else throw SubscriptionExpiredException("Невозможно продлить подписку: автообновление отключено или подписка неактивна");
}

bool Subscription::isExpired() const {
    return !isActive_;
}
