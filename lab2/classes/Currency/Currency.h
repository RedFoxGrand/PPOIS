#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Currency {
public:
    Currency(const string& code, const string& name, double exchangeRateToUsd);

    void setCode(const string& code);
    void setName(const string& name);
    void setExchangeRateToUsd(double rate);

    const string& getCode() const;
    const string& getName() const;
    double getExchangeRateToUsd() const;

    double convertToUSD(double amount, const Currency& target) const;

private:
    double exchangeRateToUsd_;
    string code_;
    string name_;
};
