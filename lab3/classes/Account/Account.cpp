#include "Account.h"

Account::Account(const Passenger& owner, const PaymentCard& card,
    const string& iban, const string& bankName,
    double balance, const string& currency) : 
    owner_(owner),
    card_(card),
    iban_(iban),
    bankName_(bankName),
    balance_(balance),
    currency_(currency) {
}

void Account::setOwner(const Passenger& owner) { 
    owner_ = owner; 
}
void Account::setCard(const PaymentCard& card) { 
    card_ = card; 
}
void Account::setIban(const string& iban) { 
    iban_ = iban; 
}
void Account::setBankName(const string& bankName) { 
    bankName_ = bankName; 
}
void Account::setBalance(double balance) { 
    balance_ = balance; 
}
void Account::setCurrency(const string& currency) { 
    currency_ = currency; 
}

const Passenger& Account::getOwner() const { 
    return owner_; 
}
const PaymentCard& Account::getCard() const { 
    return card_; 
}
const string& Account::getIban() const { 
    return iban_; 
}
const string& Account::getBankName() const { 
    return bankName_; 
}
double Account::getBalance() const { 
    return balance_; 
}
const string& Account::getCurrency() const { 
    return currency_; 
}

void Account::addFunds(double amount) {
    if (amount <= 0) throw InvalidBalanceException("Сумма пополнения не может быть отрицательной");
    balance_ += amount;
}

bool Account::deductFunds(double amount) {
    if (amount <= 0) throw InvalidBalanceException("Сумма списания не может быть отрицательной");
    if (amount > balance_) throw InvalidBalanceException("Сумма списания не может быть больше баланса");
    balance_ -= amount;

    return true;
}
