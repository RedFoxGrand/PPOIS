#pragma once
#include "PaymentCard.h"
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <exception>

using namespace std;

class Transaction {
public:
    Transaction(double amount, const string& timestamp, bool isSuccessful,
        PaymentCard& sender, PaymentCard& receiver);

    void setAmount(double amount);
    void setTimestamp(const string& timestamp);
    void setIsSuccessful(bool isSuccessful);

    double getAmount() const;
    const string& getTimestamp() const;
    bool getIsSuccessful() const;
    const PaymentCard& getSender() const;
    const PaymentCard& getReceiver() const;

    void processTransaction();

private:
    double amount_;
    string timestamp_;
    bool isSuccessful_;
    PaymentCard sender_;
    PaymentCard receiver_;

    PaymentCard* senderPtr_;
    PaymentCard* receiverPtr_;
};
