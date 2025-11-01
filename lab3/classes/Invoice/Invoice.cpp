#include "Invoice.h"

Invoice::Invoice(const string& invoiceNumber, const Passenger& passenger,
    double totalAmount, time_t timestamp, bool isPaid) : 
    invoiceNumber_(invoiceNumber),
    passenger_(passenger),
    totalAmount_(totalAmount),
    timestamp_(timestamp),
    isPaid_(isPaid) {
}

void Invoice::setInvoiceNumber(const string& invoiceNumber) {
    invoiceNumber_ = invoiceNumber; 
}
void Invoice::setPassenger(const Passenger& passenger) { 
    passenger_ = passenger;
}
void Invoice::setTotalAmount(double totalAmount) {
    totalAmount_ = totalAmount;
}
void Invoice::setTimestamp(time_t timestamp) { 
    timestamp_ = timestamp; 
}
void Invoice::setIsPaid(bool isPaid) { 
    isPaid_ = isPaid; 
}

const string& Invoice::getInvoiceNumber() const { 
    return invoiceNumber_; 
}
const Passenger& Invoice::getPassenger() const { 
    return passenger_; 
}
double Invoice::getTotalAmount() const {
    return totalAmount_; 
}
time_t Invoice::getTimestamp() const {
    return timestamp_; 
}
bool Invoice::getIsPaid() const { 
    return isPaid_; 
}

void Invoice::markPaid() {
    if (!isPaid_) isPaid_ = true;
}
