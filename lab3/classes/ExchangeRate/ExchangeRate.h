#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "InvadRateException.h"

using namespace std;

class ExchangeRate {
public:
    ExchangeRate(const string& baseCurrency, const string& targetCurrency,
        double rate, time_t lastUpdated);

    void setBaseCurrency(const string& baseCurrency);
    void setTargetCurrency(const string& targetCurrency);
    void setRate(double rate);
    void setLastUpdated(time_t lastUpdated);

    const string& getBaseCurrency() const;
    const string& getTargetCurrency() const;
    double getRate() const;
    time_t getLastUpdated() const;

    double convert(double amount) const;
    void updateRate(double newRate);

private:
    string baseCurrency_;
    string targetCurrency_;
    double rate_;
    time_t lastUpdated_;
};
