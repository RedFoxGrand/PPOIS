#include <gtest/gtest.h>
#include "PaymentCard.h"

using namespace std;

class PaymentCardTest : public ::testing::Test {
protected:
    PaymentCard* card;

    void SetUp() override {
        card = new PaymentCard("ACC123", "1234567812345678", "Иван Иванов", "12/25", 123);
    }

    void TearDown() override {
        delete card;
    }
};

TEST_F(PaymentCardTest, ConstructorInitializesValuesCorrectly) {
    EXPECT_EQ(card->getAccountId(), "ACC123");
    EXPECT_EQ(card->getCardNumber(), "1234567812345678");
    EXPECT_EQ(card->getHolderName(), "Иван Иванов");
    EXPECT_EQ(card->getExpiryDate(), "12/25");
    EXPECT_EQ(card->getCvv(), 123);
}

TEST_F(PaymentCardTest, SettersWorkCorrectly) {
    card->setAccountId("ACC999");
    card->setCardNumber("9876543210987654");
    card->setHolderName("Петр Петров");
    card->setExpiryDate("05/30");
    card->setCvv(777);

    EXPECT_EQ(card->getAccountId(), "ACC999");
    EXPECT_EQ(card->getCardNumber(), "9876543210987654");
    EXPECT_EQ(card->getHolderName(), "Петр Петров");
    EXPECT_EQ(card->getExpiryDate(), "05/30");
    EXPECT_EQ(card->getCvv(), 777);
}

TEST_F(PaymentCardTest, IsValidateReturnsTrueForCorrectData) {
    EXPECT_TRUE(card->isValidate());
}

TEST_F(PaymentCardTest, IsValidateReturnsFalseForInvalidCardNumber) {
    card->setCardNumber("1234ABC");
    EXPECT_FALSE(card->isValidate());
}

TEST_F(PaymentCardTest, IsValidateReturnsFalseForInvalidCvv) {
    card->setCvv(12);
    EXPECT_FALSE(card->isValidate());
}

TEST_F(PaymentCardTest, IsValidateReturnsFalseForInvalidExpiryFormat) {
    card->setExpiryDate("2025-12");
    EXPECT_FALSE(card->isValidate());
}

TEST_F(PaymentCardTest, AuthorizePaymentThrowsInvalidExceptionWhenCardInvalid) {
    card->setCardNumber("BADCARD");
    EXPECT_THROW(card->authorizePayment(100.0), InvalidException);
}

TEST_F(PaymentCardTest, AuthorizePaymentThrowsInvalidBalanceExceptionForNegativeAmount) {
    EXPECT_THROW(card->authorizePayment(-50.0), InvalidBalanceException);
}

TEST_F(PaymentCardTest, AuthorizePaymentDoesNotThrowForValidData) {
    EXPECT_NO_THROW(card->authorizePayment(150.0));
}
