#include <gtest/gtest.h>
#include "Wallet.h"
#include "PaymentCard.h"
#include "Transaction.h"
#include "Currency.h"

class WalletTest : public ::testing::Test {
protected:
    PaymentCard* activeCard1;
    PaymentCard* activeCard2;
    PaymentCard* inactiveCard;
    Currency* currency;
    std::vector<PaymentCard> cards;
    std::vector<Transaction> history;
    Wallet* wallet;

    void SetUp() override {
        activeCard1 = new PaymentCard("1111222233334444", "12/30", "User One", 123, 100.0, true);
        activeCard2 = new PaymentCard("5555666677778888", "12/30", "User Two", 456, 50.0, true);
        inactiveCard = new PaymentCard("9999000011112222", "12/30", "Inactive User", 789, 200.0, false);
        currency = new Currency("BYN", "Belarusian Ruble", 1.0);

        cards = { *activeCard1, *activeCard2, *inactiveCard };
        history = {};
        wallet = new Wallet(500.0, cards, history, *currency);
    }

    void TearDown() override {
        delete activeCard1;
        delete activeCard2;
        delete inactiveCard;
        delete currency;
        delete wallet;
    }
};

TEST_F(WalletTest, ConstructorInitializesCorrectly) {
    EXPECT_DOUBLE_EQ(wallet->getBalance(), 500.0);
    EXPECT_EQ(wallet->getCards().size(), 3);
    EXPECT_EQ(wallet->getCurrency().getCode(), "BYN");
    EXPECT_TRUE(wallet->getCards()[0].getIsActive());
    EXPECT_FALSE(wallet->getCards()[2].getIsActive());
}

TEST_F(WalletTest, SettersAndGettersWorkCorrectly) {
    Currency newCurrency("USD", "US Dollar", 3.25);
    wallet->setBalance(1000.0);
    wallet->setCurrency(newCurrency);

    EXPECT_DOUBLE_EQ(wallet->getBalance(), 1000.0);
    EXPECT_EQ(wallet->getCurrency().getCode(), "USD");
    EXPECT_DOUBLE_EQ(wallet->getCurrency().getExchangeRateToUsd(), 3.25);
}

TEST_F(WalletTest, GetWalletBalanceCountsOnlyActiveCards) {
    EXPECT_DOUBLE_EQ(wallet->getWalletBalance(), 150.0);
}

TEST_F(WalletTest, AddCardAddsCardToWallet) {
    PaymentCard newCard("3333444455556666", "12/31", "New User", 321, 300.0, true);
    size_t initialSize = wallet->getCards().size();

    wallet->addCard(newCard);

    EXPECT_EQ(wallet->getCards().size(), initialSize + 1);
    EXPECT_EQ(wallet->getCards().back().getCardNumber(), "3333444455556666");
}

TEST_F(WalletTest, SetAndGetHistoryWorks) {
    PaymentCard sender("1111222233334444", "12/30", "Sender", 123, 100.0, true);
    PaymentCard receiver("5555666677778888", "12/30", "Receiver", 456, 50.0, true);

    Transaction transaction(25.0, "2025-10-24 12:00:00", true, sender, receiver);
    std::vector<Transaction> newHistory = { transaction };

    wallet->setHistory(newHistory);

    EXPECT_EQ(wallet->getHistory().size(), 1);
    EXPECT_DOUBLE_EQ(wallet->getHistory()[0].getAmount(), 25.0);
    EXPECT_TRUE(wallet->getHistory()[0].getIsSuccessful());
}

TEST_F(WalletTest, SetCardsReplacesExistingCards) {
    PaymentCard cardA("1111", "11/25", "A", 111, 10.0, true);
    PaymentCard cardB("2222", "11/26", "B", 222, 20.0, true);
    std::vector<PaymentCard> newCards = { cardA, cardB };

    wallet->setCards(newCards);

    EXPECT_EQ(wallet->getCards().size(), 2);
    EXPECT_EQ(wallet->getCards()[0].getCardNumber(), "1111");
    EXPECT_EQ(wallet->getCards()[1].getCardNumber(), "2222");
}
