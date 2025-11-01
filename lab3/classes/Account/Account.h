#pragma once
#include <iostream>
#include <string>
#include "Passenger.h"
#include "PaymentCard.h"
#include "InvalidBalanceException.h"

using namespace std;

class Account {
public:
    Account(const Passenger& owner, const PaymentCard& card,
        const string& iban, const string& bankName,
        double balance, const string& currency);

    void setOwner(const Passenger& owner);
    void setCard(const PaymentCard& card);
    void setIban(const string& iban);
    void setBankName(const string& bankName);
    void setBalance(double balance);
    void setCurrency(const string& currency);

    const Passenger& getOwner() const;
    const PaymentCard& getCard() const;
    const string& getIban() const;
    const string& getBankName() const;
    double getBalance() const;
    const string& getCurrency() const;

    void addFunds(double amount);
    bool deductFunds(double amount);

private:
    Passenger owner_;
    PaymentCard card_;
    string iban_;
    string bankName_;
    double balance_;
    string currency_;
};
