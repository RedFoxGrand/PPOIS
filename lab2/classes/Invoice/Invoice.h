#pragma once
#include "User.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

enum class InvoiceStatus { PENDING, PAID, OVERDUE };

class Invoice {
public:
    bool isOverdue() const;
    void markAsPaid();

    void setAmount(double amount);
    void setDueDate(const string& dueDate);
    void setPayer(const User& payer);
    void setStatus(InvoiceStatus status);

    double getAmount() const;
    const string& getDueDate() const;
    const User& getPayer() const;
    InvoiceStatus getStatus() const;

    Invoice(double amount, const string& dueDate, const User& payer, InvoiceStatus status);

private:
    double amount_;
    string dueDate_;
    User payer_;
    InvoiceStatus status_;
};
