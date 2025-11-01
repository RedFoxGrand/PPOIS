#include "Visa.h"
#include <iomanip>

Visa::Visa(const string& visaNumber, const string& country,
    time_t issueDate, time_t expiryDate, VisaType type) : 
    visaNumber_(visaNumber),
    country_(country),
    issueDate_(issueDate),
    expiryDate_(expiryDate),
    type_(type) {
}

void Visa::setVisaNumber(const string& visaNumber) {
    visaNumber_ = visaNumber; 
}
void Visa::setCountry(const string& country) { 
    country_ = country; 
}
void Visa::setIssueDate(time_t issueDate) { 
    issueDate_ = issueDate; 
}
void Visa::setExpiryDate(time_t expiryDate) {
    expiryDate_ = expiryDate; 
}
void Visa::setType(VisaType type) {
    type_ = type;
}

const string& Visa::getVisaNumber() const {
    return visaNumber_;
}
const string& Visa::getCountry() const {
    return country_; 
}
time_t Visa::getIssueDate() const {
    return issueDate_; 
}
time_t Visa::getExpiryDate() const {
    return expiryDate_; 
}
VisaType Visa::getType() const { 
    return type_; 
}

bool Visa::isExpired() const {
    time_t now = time(nullptr);
    return difftime(now, expiryDate_) > 0;
}

void Visa::renew(time_t newExpiry) {
    if (newExpiry > expiryDate_) expiryDate_ = newExpiry;
    else throw ExpiredException("Ошибка продления визы");
}
