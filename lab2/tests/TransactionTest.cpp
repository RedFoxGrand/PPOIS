#include <gtest/gtest.h>
#include "Transaction.h"
#include "PaymentCard.h"
#include "Exception.h"

class TransactionTest : public ::testing::Test {
protected:
    PaymentCard* senderActive;
    PaymentCard* receiverActive;
    PaymentCard* senderInactive;
    PaymentCard* receiverInactive;

    void SetUp() override {
        senderActive = new PaymentCard("1111222233334444", "12/30", "Sender User", 123, 100.0, true);
        receiverActive = new PaymentCard("5555666677778888", "12/30", "Receiver User", 456, 50.0, true);
        senderInactive = new PaymentCard("9999888877776666", "12/30", "Inactive Sender", 789, 100.0, false);
        receiverInactive = new PaymentCard("2222333344445555", "12/30", "Inactive Receiver", 101, 50.0, false);
    }

    void TearDown() override {
        delete senderActive;
        delete receiverActive;
        delete senderInactive;
        delete receiverInactive;
    }
};

TEST_F(TransactionTest, SuccessfulTransaction) {
    Transaction transaction(40.0, "", false, *senderActive, *receiverActive);

    EXPECT_NO_THROW(transaction.processTransaction());
    EXPECT_TRUE(transaction.getIsSuccessful());
    EXPECT_DOUBLE_EQ(senderActive->getBalance(), 60.0);
    EXPECT_DOUBLE_EQ(receiverActive->getBalance(), 90.0);
    EXPECT_FALSE(transaction.getTimestamp().empty());
}

TEST_F(TransactionTest, SenderCardInactive) {
    Transaction transaction(40.0, "", false, *senderInactive, *receiverActive);

    EXPECT_THROW(transaction.processTransaction(), CardExpiredException);
    EXPECT_FALSE(transaction.getIsSuccessful());
}

TEST_F(TransactionTest, ReceiverCardInactive) {
    Transaction transaction(40.0, "", false, *senderActive, *receiverInactive);

    EXPECT_THROW(transaction.processTransaction(), CardExpiredException);
    EXPECT_FALSE(transaction.getIsSuccessful());
}

TEST_F(TransactionTest, InsufficientFunds) {
    PaymentCard lowBalanceSender = *senderActive;
    lowBalanceSender.setBalance(30.0);

    Transaction transaction(40.0, "", false, lowBalanceSender, *receiverActive);

    EXPECT_THROW(transaction.processTransaction(), InsufficientFundsException);
    EXPECT_FALSE(transaction.getIsSuccessful());
}

TEST_F(TransactionTest, NegativeAmount) {
    Transaction transaction(-10.0, "", false, *senderActive, *receiverActive);

    EXPECT_THROW(transaction.processTransaction(), InsufficientFundsException);
    EXPECT_FALSE(transaction.getIsSuccessful());
}
