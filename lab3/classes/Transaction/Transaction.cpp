#include "Transaction.h"

Transaction::Transaction(const string& transactionId, double amount, time_t timestamp, bool success) : 
    transactionId_(transactionId),
    amount_(amount),
    timestamp_(timestamp),
    success_(success) {
}

void Transaction::setTransactionId(const string& transactionId) { 
    transactionId_ = transactionId;
}
void Transaction::setAmount(double amount) {
    amount_ = amount;
}
void Transaction::setTimestamp(time_t timestamp) { 
    timestamp_ = timestamp; 
}
void Transaction::setSuccess(bool success) { 
    success_ = success; 
}

const string& Transaction::getTransactionId() const {
    return transactionId_; 
}
double Transaction::getAmount() const { 
    return amount_; 
}
time_t Transaction::getTimestamp() const {
    return timestamp_; 
}
bool Transaction::isSuccessful() const {
    return success_;
}

void Transaction::processTransaction(PaymentCard& card, Account& destination, double amount) {
    if (!card.isValidate()) {
        success_ = false;
        throw InvalidException("Карта не действительна");
    }

    if (amount <= 0) {
        success_ = false;
        throw InvalidBalanceException("Сумма не может быть отрицательной");
    }

    destination.addFunds(amount);
}

void Transaction::processRefund(Account& source, PaymentCard& card, double amount) {
    if (amount <= 0) {
        success_ = false;
        throw InvalidBalanceException("Сумма пополнения не может быть отрицательной");
    }

    if (!source.deductFunds(amount)) {
        success_ = false;
        return;
    }

    if (!card.isValidate()) {
        success_ = false;
        throw InvalidException("Карта не действительна");
    }
}
