#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "Visa.h"

using namespace std;

enum class MaritalStatus { Married, NotMarried, Widower, Divorced };

class Passport {
public:
    Passport(const string& passportNumber, const string& country,
        const string& holderName, time_t issueDate, time_t expiryDate,
        const Visa& visa, MaritalStatus status);

    void setPassportNumber(const string& passportNumber);
    void setCountry(const string& country);
    void setHolderName(const string& holderName);
    void setIssueDate(time_t issueDate);
    void setExpiryDate(time_t expiryDate);
    void setVisa(const Visa& visa);
    void setMaritalStatus(MaritalStatus status);

    const string& getPassportNumber() const;
    const string& getCountry() const;
    const string& getHolderName() const;
    time_t getIssueDate() const;
    time_t getExpiryDate() const;
    const Visa& getVisa() const;
    MaritalStatus getMaritalStatus() const;

    void renew(time_t newExpiryDate);
    MaritalStatus changeMaritalStatus(MaritalStatus newStatus);

private:
    string passportNumber_;
    string country_;
    string holderName_;
    time_t issueDate_;
    time_t expiryDate_;
    Visa visa_;
    MaritalStatus status_;
};
