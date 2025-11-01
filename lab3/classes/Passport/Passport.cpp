#include "Passport.h"

Passport::Passport(const string& passportNumber, const string& country,
    const string& holderName, time_t issueDate, time_t expiryDate,
    const Visa& visa, MaritalStatus status) :
    passportNumber_(passportNumber),
    country_(country),
    holderName_(holderName),
    issueDate_(issueDate),
    expiryDate_(expiryDate),
    visa_(visa),
    status_(status) {
}

void Passport::setPassportNumber(const string& passportNumber) {
    passportNumber_ = passportNumber;
}
void Passport::setCountry(const string& country) {
    country_ = country;
}
void Passport::setHolderName(const string& holderName) {
    holderName_ = holderName;
}
void Passport::setIssueDate(time_t issueDate) {
    issueDate_ = issueDate;
}
void Passport::setExpiryDate(time_t expiryDate) {
    expiryDate_ = expiryDate;
}
void Passport::setVisa(const Visa& visa) {
    visa_ = visa;
}
void Passport::setMaritalStatus(MaritalStatus status) {
    status_ = status;
}

const string& Passport::getPassportNumber() const {
    return passportNumber_;
}
const string& Passport::getCountry() const {
    return country_;
}
const string& Passport::getHolderName() const {
    return holderName_;
}
time_t Passport::getIssueDate() const {
    return issueDate_;
}
time_t Passport::getExpiryDate() const {
    return expiryDate_;
}
const Visa& Passport::getVisa() const {
    return visa_;
}
MaritalStatus Passport::getMaritalStatus() const {
    return status_;
}

void Passport::renew(time_t newExpiryDate) {
    if (newExpiryDate > expiryDate_) expiryDate_ = newExpiryDate;
    else return;
}

MaritalStatus Passport::changeMaritalStatus(MaritalStatus newStatus) {
    status_ = newStatus;
    return status_;
}
