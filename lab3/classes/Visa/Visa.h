#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "ExpiredException.h"

using namespace std;

enum class VisaType { Tourist, Business, Work, Educational, Guest };

class Visa {
public:
    Visa(const string& visaNumber, const string& country,
        time_t issueDate, time_t expiryDate, VisaType type);

    void setVisaNumber(const string& visaNumber);
    void setCountry(const string& country);
    void setIssueDate(time_t issueDate);
    void setExpiryDate(time_t expiryDate);
    void setType(VisaType type);

    const string& getVisaNumber() const;
    const string& getCountry() const;
    time_t getIssueDate() const;
    time_t getExpiryDate() const;
    VisaType getType() const;

    bool isExpired() const;
    void renew(time_t newExpiry);

private:
    string visaNumber_;
    string country_;
    time_t issueDate_;
    time_t expiryDate_;
    VisaType type_;
};
