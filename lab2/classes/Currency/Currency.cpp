#include "Currency.h"

Currency::Currency(const string& code, const string& name, double exchangeRateToUsd) :
    code_(code),
    name_(name),
    exchangeRateToUsd_(exchangeRateToUsd) {
}

void Currency::setCode(const string& code) {
    code_ = code;
}
void Currency::setName(const string& name) {
    name_ = name;
}
void Currency::setExchangeRateToUsd(double rate) {
    exchangeRateToUsd_ = rate;
}

const string& Currency::getCode() const {
    return code_;
}
const string& Currency::getName() const {
    return name_;
}
double Currency::getExchangeRateToUsd() const {
    return exchangeRateToUsd_;
}

double Currency::convertToUSD(double amount, const Currency& target) const {
    if (target.exchangeRateToUsd_ == 0.0) return 0.0;

    return amount * exchangeRateToUsd_ / target.exchangeRateToUsd_;
}
