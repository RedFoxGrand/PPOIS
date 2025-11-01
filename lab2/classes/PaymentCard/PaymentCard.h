#pragma once
#include "InsufficientFundsException.h"
#include "CardExpiredException.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <exception>

using namespace std;

class PaymentCard {
public:
    PaymentCard(const string& cardNumber, const string& expiryDate, const string& cardHolderName,
        int cvv, double balance, bool isActive);

    void setCardNumber(const string& cardNumber);
    void setExpiryDate(const string& expiryDate);
    void setCardHolderName(const string& cardHolderName);
    void setCvv(int cvv);
    void setBalance(double balance);
    void setIsActive(bool isActive);

    const string& getCardNumber() const;
    const string& getExpiryDate() const;
    const string& getCardHolderName() const;
    int getCvv() const;
    double getBalance() const;
    bool getIsActive() const;

    void debit(double amount);
    void credit(double amount);
    bool isValidCard() const;

private:
    int cvv_;
    double balance_;
    string cardNumber_;
    string expiryDate_;
    string cardHolderName_;
    bool isActive_;
};
