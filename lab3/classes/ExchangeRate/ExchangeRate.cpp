#include "ExchangeRate.h"

ExchangeRate::ExchangeRate(const string& baseCurrency, const string& targetCurrency,
    double rate, time_t lastUpdated) : 
    baseCurrency_(baseCurrency),
    targetCurrency_(targetCurrency),
    rate_(rate),
    lastUpdated_(lastUpdated) {
}

void ExchangeRate::setBaseCurrency(const string& baseCurrency) { 
    baseCurrency_ = baseCurrency; 
}
void ExchangeRate::setTargetCurrency(const string& targetCurrency) { 
    targetCurrency_ = targetCurrency; 
}
void ExchangeRate::setRate(double rate) { 
    rate_ = rate; 
}
void ExchangeRate::setLastUpdated(time_t lastUpdated) { 
    lastUpdated_ = lastUpdated; 
}

const string& ExchangeRate::getBaseCurrency() const { 
    return baseCurrency_; 
}
const string& ExchangeRate::getTargetCurrency() const { 
    return targetCurrency_; 
}
double ExchangeRate::getRate() const { 
    return rate_; 
}
time_t ExchangeRate::getLastUpdated() const { 
    return lastUpdated_; 
}

double ExchangeRate::convert(double amount) const {
    if (amount < 0) return 0.0;
    return amount * rate_;
}

void ExchangeRate::updateRate(double newRate) {
    if (newRate <= 0) throw InvadRateException("Курс не может быть отрицательным");
    rate_ = newRate;
    lastUpdated_ = time(nullptr);
}
