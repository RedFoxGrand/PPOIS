#include "Transaction.h"

Transaction::Transaction(double amount, const string& timestamp, bool isSuccessful,
    PaymentCard& sender, PaymentCard& receiver) : 
    amount_(amount),
    timestamp_(timestamp),
    isSuccessful_(isSuccessful),
    sender_(sender),
    receiver_(receiver),
    senderPtr_(&sender),
    receiverPtr_(&receiver) {
}

void Transaction::setAmount(double amount) {
    amount_ = amount;
}

void Transaction::setTimestamp(const string& timestamp) {
    timestamp_ = timestamp;
}

void Transaction::setIsSuccessful(bool isSuccessful) {
    isSuccessful_ = isSuccessful;
}

double Transaction::getAmount() const {
    return amount_;
}

const string& Transaction::getTimestamp() const {
    return timestamp_;
}

bool Transaction::getIsSuccessful() const {
    return isSuccessful_;
}

const PaymentCard& Transaction::getSender() const {
    return sender_;
}

const PaymentCard& Transaction::getReceiver() const {
    return receiver_;
}

void Transaction::processTransaction() {
    if (amount_ <= 0.0) {
        isSuccessful_ = false;
        throw InsufficientFundsException("Сумма транзакции должна быть положительной");
    }

    if (!senderPtr_->getIsActive()) {
        isSuccessful_ = false;
        throw CardExpiredException("Карта отправителя неактивна");
    }

    if (!receiverPtr_->getIsActive()) {
        isSuccessful_ = false;
        throw CardExpiredException("Карта получателя неактивна");
    }

    if (senderPtr_->getBalance() < amount_) {
        isSuccessful_ = false;
        throw InsufficientFundsException("Недостаточно средств на карте");
    }

    senderPtr_->debit(amount_);
    receiverPtr_->credit(amount_);

    isSuccessful_ = true;

    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    tm timeInfo{};
    localtime_s(&timeInfo, &time);

    stringstream ss;
    ss << put_time(&timeInfo, "%d.%m.%Y %H:%M:%S");
    timestamp_ = ss.str();
}
