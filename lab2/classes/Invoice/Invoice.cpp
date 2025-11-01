#include "Invoice.h"

Invoice::Invoice(double amount, const string& dueDate, const User& payer, InvoiceStatus status) :
    amount_(amount),
    dueDate_(dueDate),
    payer_(payer),
    status_(status) {
}

void Invoice::setAmount(double amount) {
    amount_ = amount;
}
void Invoice::setDueDate(const string& dueDate) {
    dueDate_ = dueDate;
}
void Invoice::setPayer(const User& payer) {
    payer_ = payer;
}
void Invoice::setStatus(InvoiceStatus status) {
    status_ = status;
}

double Invoice::getAmount() const {
    return amount_;
}
const string& Invoice::getDueDate() const {
    return dueDate_;
}
const User& Invoice::getPayer() const {
    return payer_;
}
InvoiceStatus Invoice::getStatus() const {
    return status_;
}

bool Invoice::isOverdue() const {
    return status_ == InvoiceStatus::OVERDUE;
}

void Invoice::markAsPaid() {
    status_ = InvoiceStatus::PAID;
}
