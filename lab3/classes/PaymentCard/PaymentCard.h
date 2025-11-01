#pragma once
#include <iostream>
#include <string>
#include <regex>
#include "InvalidBalanceException.h"
#include "InvalidException.h"

using namespace std;

class PaymentCard {
public:
    PaymentCard(const string& accountId, const string& cardNumber,
        const string& holderName, const string& expiryDate, int cvv);

    void setAccountId(const string& accountId);
    void setCardNumber(const string& cardNumber);
    void setHolderName(const string& holderName);
    void setExpiryDate(const string& expiryDate);
    void setCvv(int cvv);

    const string& getAccountId() const;
    const string& getCardNumber() const;
    const string& getHolderName() const;
    const string& getExpiryDate() const;
    int getCvv() const;

    void authorizePayment(double amount);
    bool isValidate() const;

private:
    string accountId_;
    string cardNumber_;
    string holderName_;
    string expiryDate_;
    int cvv_;
};
