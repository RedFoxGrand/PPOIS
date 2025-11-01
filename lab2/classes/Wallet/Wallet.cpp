#include "Wallet.h"

Wallet::Wallet(double balance, const vector<PaymentCard>& cards, const vector<Transaction>& history, const Currency& currency) :
    balance_(balance),
    cards_(cards),
    history_(history),
    currency_(currency) {
}

void Wallet::setBalance(double balance) {
    balance_ = balance;
}
void Wallet::setCards(const vector<PaymentCard>& cards) {
    cards_ = cards;
}
void Wallet::setHistory(const vector<Transaction>& history) {
    history_ = history;
}
void Wallet::setCurrency(const Currency& currency) {
    currency_ = currency;
}

double Wallet::getBalance() const {
    return balance_;
}
const vector<PaymentCard>& Wallet::getCards() const {
    return cards_;
}
const vector<Transaction>& Wallet::getHistory() const {
    return history_;
}
const Currency& Wallet::getCurrency() const {
    return currency_;
}

double Wallet::getWalletBalance() const {
    double total = 0.0;
    for (const auto& card : cards_) if (card.getIsActive()) total += card.getBalance();

    return total;
}

void Wallet::addCard(const PaymentCard& card) {
    cards_.push_back(card);
}
