#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "Account.h"
#include "InvalidBalanceException.h"
#include "InvalidException.h"

using namespace std;

class Transaction {
public:
    Transaction(const string& transactionId, double amount, time_t timestamp, bool success);

    void setTransactionId(const string& transactionId);
    void setAmount(double amount);
    void setTimestamp(time_t timestamp);
    void setSuccess(bool success);

    const string& getTransactionId() const;
    double getAmount() const;
    time_t getTimestamp() const;
    bool isSuccessful() const;

    void processTransaction(PaymentCard& card, Account& destination, double amount);
    void processRefund(Account& source, PaymentCard& card, double amount);

private:
    string transactionId_;
    double amount_;
    time_t timestamp_;
    bool success_;
};
