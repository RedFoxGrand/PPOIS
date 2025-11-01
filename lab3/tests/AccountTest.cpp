#include <gtest/gtest.h>
#include "Account.h"

class AccountTest : public ::testing::Test {
protected:
    ContactInfo* contact; Visa* visa; Passport* passport; Passenger* passenger;
    PaymentCard* card; Account* account; time_t birthDate; time_t issueDate; time_t expiryDate;

    void SetUp() override {
        birthDate = time(nullptr) - 86400 * 365 * 30;
        issueDate = time(nullptr) - 86400 * 100;
        expiryDate = time(nullptr) + 86400 * 365;

        contact = new ContactInfo("test@mail.com", "+79001234567", "Москва, Россия");
        visa = new Visa("VISA1", "France", issueDate, expiryDate, VisaType::Tourist);
        passport = new Passport("P123456", "Россия", "Иван Петров", issueDate, expiryDate, *visa, MaritalStatus::NotMarried);

        passenger = new Passenger("Иван", "Петров", birthDate, *contact, "PSG001", *passport);
        card = new PaymentCard("ACC001", "1234567812345678", "Иван Петров", "12/30", 123);
        account = new Account(*passenger, *card, "RU1234567890", "СберБанк", 1000.0, "RUB");
    }

    void TearDown() override {
        delete contact; delete visa; delete passport;
        delete passenger; delete card; delete account;
    }
};

TEST_F(AccountTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(account->getOwner().getPassengerId(), "PSG001");
    EXPECT_EQ(account->getCard().getCardNumber(), "1234567812345678");
    EXPECT_EQ(account->getIban(), "RU1234567890");
    EXPECT_EQ(account->getBankName(), "СберБанк");
    EXPECT_DOUBLE_EQ(account->getBalance(), 1000.0);
    EXPECT_EQ(account->getCurrency(), "RUB");
}

TEST_F(AccountTest, SettersWorkCorrectly) {
    PaymentCard newCard("ACC002", "8765432187654321", "Ivan Petrov", "01/29", 456);
    Passenger newPassenger("Пётр", "Сидоров", birthDate, *contact, "PSG777", *passport);

    account->setOwner(newPassenger);
    account->setCard(newCard);
    account->setIban("RU9999");
    account->setBankName("ВТБ");
    account->setBalance(5000.0);
    account->setCurrency("USD");

    EXPECT_EQ(account->getOwner().getName(), "Пётр");
    EXPECT_EQ(account->getCard().getCardNumber(), "8765432187654321");
    EXPECT_EQ(account->getIban(), "RU9999");
    EXPECT_EQ(account->getBankName(), "ВТБ");
    EXPECT_DOUBLE_EQ(account->getBalance(), 5000.0);
    EXPECT_EQ(account->getCurrency(), "USD");
}

TEST_F(AccountTest, AddFundsIncreasesBalance) {
    account->addFunds(200.0);
    EXPECT_DOUBLE_EQ(account->getBalance(), 1200.0);
}

TEST_F(AccountTest, AddFundsThrowsIfNegative) {
    EXPECT_THROW(account->addFunds(-100.0), InvalidBalanceException);
    EXPECT_THROW(account->addFunds(0), InvalidBalanceException);
}

TEST_F(AccountTest, DeductFundsDecreasesBalance) {
    bool result = account->deductFunds(400.0);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(account->getBalance(), 600.0);
}

TEST_F(AccountTest, DeductFundsThrowsIfNegativeOrZero) {
    EXPECT_THROW(account->deductFunds(-50.0), InvalidBalanceException);
    EXPECT_THROW(account->deductFunds(0.0), InvalidBalanceException);
}

TEST_F(AccountTest, DeductFundsThrowsIfMoreThanBalance) {
    EXPECT_THROW(account->deductFunds(2000.0), InvalidBalanceException);
}
