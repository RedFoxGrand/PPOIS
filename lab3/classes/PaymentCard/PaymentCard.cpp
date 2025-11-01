#include "PaymentCard.h"

PaymentCard::PaymentCard(const string& accountId, const string& cardNumber,
    const string& holderName, const string& expiryDate, int cvv) : 
    accountId_(accountId),
    cardNumber_(cardNumber),
    holderName_(holderName),
    expiryDate_(expiryDate),
    cvv_(cvv) {
}

void PaymentCard::setAccountId(const string& accountId) { 
    accountId_ = accountId; 
}
void PaymentCard::setCardNumber(const string& cardNumber) { 
    cardNumber_ = cardNumber; 
}
void PaymentCard::setHolderName(const string& holderName) { 
    holderName_ = holderName; 
}
void PaymentCard::setExpiryDate(const string& expiryDate) { 
    expiryDate_ = expiryDate; 
}
void PaymentCard::setCvv(int cvv) { 
    cvv_ = cvv; 
}

const string& PaymentCard::getAccountId() const { 
    return accountId_;
}
const string& PaymentCard::getCardNumber() const {
    return cardNumber_; 
}
const string& PaymentCard::getHolderName() const {
    return holderName_; 
}
const string& PaymentCard::getExpiryDate() const { 
    return expiryDate_; 
}
int PaymentCard::getCvv() const {
    return cvv_;
}

bool PaymentCard::isValidate() const {
    if (cardNumber_.length() != 16 || !regex_match(cardNumber_, regex("^[0-9]+$"))) return false;
    if (cvv_ < 100 || cvv_ > 9999) return false;
    if (!regex_match(expiryDate_, regex("^(0[1-9]|1[0-2])/([0-9]{2})$"))) return false;

    return true;
}

void PaymentCard::authorizePayment(double amount) {
    if (!isValidate()) throw InvalidException("Карта не действительна");
    if (amount <= 0) throw InvalidBalanceException("Сумма не может быть отрицательной");
}
