#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "Passenger.h"

using namespace std;

class Invoice {
public:
    Invoice(const string& invoiceNumber, const Passenger& passenger,
        double totalAmount, time_t timestamp, bool isPaid);

    void setInvoiceNumber(const string& invoiceNumber);
    void setPassenger(const Passenger& passenger);
    void setTotalAmount(double totalAmount);
    void setTimestamp(time_t timestamp);
    void setIsPaid(bool isPaid);

    const string& getInvoiceNumber() const;
    const Passenger& getPassenger() const;
    double getTotalAmount() const;
    time_t getTimestamp() const;
    bool getIsPaid() const;

    void markPaid();

private:
    string invoiceNumber_;
    Passenger passenger_;
    double totalAmount_;
    time_t timestamp_;
    bool isPaid_;
};
