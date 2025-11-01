#include <gtest/gtest.h>
#include "Transaction.h"

class TransactionTest : public ::testing::Test {
protected:
    ContactInfo* contact; Visa* visa; Passport* passport; Passenger* passenger;
    PaymentCard* card; Account* account; Transaction* transaction;
    time_t birthDate; time_t issueDate; time_t expiryDate; time_t now;

    void SetUp() override {
        now = time(nullptr);
        birthDate = now - 86400 * 365 * 30;
        issueDate = now - 86400 * 100;
        expiryDate = now + 86400 * 365;

        contact = new ContactInfo("test@mail.com", "+79001234567", "Москва, Россия");
        visa = new Visa("V001", "Франция", issueDate, expiryDate, VisaType::Tourist);
        passport = new Passport("PP123456", "Россия", "Сергей Иванов", issueDate, expiryDate, *visa, MaritalStatus::NotMarried);
        passenger = new Passenger("Сергей", "Иванов", birthDate, *contact, "PSG001", *passport);

        card = new PaymentCard("ACC001", "1234567812345678", "Сергей Иванов", "12/30", 123);
        account = new Account(*passenger, *card, "RU1234567890", "Сбербанк", 1000.0, "RUB");
        transaction = new Transaction("TX001", 0.0, now, false);
    }

    void TearDown() override {
        delete contact; delete visa; delete passport; delete passenger;
        delete card; delete account; delete transaction;
    }
};

TEST_F(TransactionTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(transaction->getTransactionId(), "TX001");
    EXPECT_DOUBLE_EQ(transaction->getAmount(), 0.0);
    EXPECT_FALSE(transaction->isSuccessful());
}

TEST_F(TransactionTest, SettersWorkCorrectly) {
    transaction->setTransactionId("TX999");
    transaction->setAmount(500.0);
    transaction->setTimestamp(now + 1000);
    transaction->setSuccess(true);

    EXPECT_EQ(transaction->getTransactionId(), "TX999");
    EXPECT_DOUBLE_EQ(transaction->getAmount(), 500.0);
    EXPECT_TRUE(transaction->isSuccessful());
    EXPECT_GT(transaction->getTimestamp(), now);
}

TEST_F(TransactionTest, ProcessTransactionAddsFundsCorrectly) {
    double initial = account->getBalance();
    transaction->processTransaction(*card, *account, 300.0);

    EXPECT_DOUBLE_EQ(account->getBalance(), initial + 300.0);
}

TEST_F(TransactionTest, ProcessTransactionThrowsIfCardInvalid) {
    card->setCardNumber("invalid");
    EXPECT_THROW(transaction->processTransaction(*card, *account, 200.0), InvalidException);
    EXPECT_FALSE(transaction->isSuccessful());
}

TEST_F(TransactionTest, ProcessTransactionThrowsIfNegativeAmount) {
    EXPECT_THROW(transaction->processTransaction(*card, *account, -100.0), InvalidBalanceException);
    EXPECT_FALSE(transaction->isSuccessful());
}

TEST_F(TransactionTest, ProcessRefundDeductsFundsCorrectly) {
    double initial = account->getBalance();
    transaction->processRefund(*account, *card, 200.0);
    EXPECT_DOUBLE_EQ(account->getBalance(), initial - 200.0);
}

TEST_F(TransactionTest, ProcessRefundThrowsIfNegativeAmount) {
    EXPECT_THROW(transaction->processRefund(*account, *card, -50.0), InvalidBalanceException);
    EXPECT_FALSE(transaction->isSuccessful());
}

TEST_F(TransactionTest, ProcessRefundThrowsIfCardInvalid) {
    card->setCardNumber("badnumber");
    EXPECT_THROW(transaction->processRefund(*account, *card, 100.0), InvalidException);
    EXPECT_FALSE(transaction->isSuccessful());
}

TEST_F(TransactionTest, ProcessRefundThrowsIfInsufficientFunds) {
    EXPECT_THROW(transaction->processRefund(*account, *card, 5000.0), InvalidBalanceException);
    EXPECT_FALSE(transaction->isSuccessful());
}
