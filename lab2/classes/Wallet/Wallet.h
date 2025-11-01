#pragma once
#include "PaymentCard.h"
#include "Transaction.h"
#include "Currency.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Wallet {
public:
    Wallet(double balance, const vector<PaymentCard>& cards, const vector<Transaction>& history, const Currency& currency);

    void setBalance(double balance);
    void setCards(const vector<PaymentCard>& cards);
    void setHistory(const vector<Transaction>& history);
    void setCurrency(const Currency& currency);

    double getBalance() const;
    const vector<PaymentCard>& getCards() const;
    const vector<Transaction>& getHistory() const;
    const Currency& getCurrency() const;

    double getWalletBalance() const;
    void addCard(const PaymentCard& card);

private:
    double balance_;
    vector<PaymentCard> cards_;
    vector<Transaction> history_;
    Currency currency_;
};
