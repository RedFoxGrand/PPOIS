#include <gtest/gtest.h>
#include "PaymentCard.h"
#include "Exception.h"

using namespace std;

class PaymentCardTest : public ::testing::Test {
protected:
    PaymentCard* card;

    void SetUp() override {
        card = new PaymentCard("1234567890123456", "12/30", "Иван Иванов", 123, 1000.0, true);
    }

    void TearDown() override {
        delete card;
    }
};

TEST_F(PaymentCardTest, ConstructorAndGetters) {
    EXPECT_EQ(card->getCardNumber(), "1234567890123456");
    EXPECT_EQ(card->getExpiryDate(), "12/30");
    EXPECT_EQ(card->getCardHolderName(), "Иван Иванов");
    EXPECT_EQ(card->getCvv(), 123);
    EXPECT_DOUBLE_EQ(card->getBalance(), 1000.0);
    EXPECT_TRUE(card->getIsActive());
}

TEST_F(PaymentCardTest, SettersChangeValues) {
    card->setCardNumber("9999888877776666");
    card->setExpiryDate("10/28");
    card->setCardHolderName("Петр Петров");
    card->setCvv(999);
    card->setBalance(500.5);
    card->setIsActive(false);

    EXPECT_EQ(card->getCardNumber(), "9999888877776666");
    EXPECT_EQ(card->getExpiryDate(), "10/28");
    EXPECT_EQ(card->getCardHolderName(), "Петр Петров");
    EXPECT_EQ(card->getCvv(), 999);
    EXPECT_DOUBLE_EQ(card->getBalance(), 500.5);
    EXPECT_FALSE(card->getIsActive());
}

TEST_F(PaymentCardTest, DebitSuccessful) {
    testing::internal::CaptureStdout();
    card->debit(200.0);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_DOUBLE_EQ(card->getBalance(), 800.0);
}

TEST_F(PaymentCardTest, DebitInsufficientFunds) {
    EXPECT_THROW(card->debit(2000.0), InsufficientFundsException);
}

TEST_F(PaymentCardTest, DebitInactiveCard) {
    card->setIsActive(false);
    EXPECT_THROW(card->debit(100.0), CardExpiredException);
}

TEST_F(PaymentCardTest, CreditSuccessful) {
    testing::internal::CaptureStdout();
    card->credit(300.0);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_DOUBLE_EQ(card->getBalance(), 1300.0);
}

TEST_F(PaymentCardTest, CreditNegativeAmount) {
    EXPECT_THROW(card->credit(-50.0), InsufficientFundsException);
}

TEST_F(PaymentCardTest, InvalidInactiveCard) {
    card->setIsActive(false);
    EXPECT_THROW(card->isValidCard(), CardExpiredException);
}

TEST_F(PaymentCardTest, InvalidExpiryDateFormat) {
    card->setExpiryDate("1230");
    testing::internal::CaptureStdout();
    bool result = card->isValidCard();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(result);
}

TEST_F(PaymentCardTest, InvalidMonthInExpiryDate) {
    card->setExpiryDate("13/30");
    testing::internal::CaptureStdout();
    bool result = card->isValidCard();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(result);
}

TEST_F(PaymentCardTest, ExpiredCard) {
    card->setExpiryDate("01/20");
    EXPECT_THROW(card->isValidCard(), CardExpiredException);
}

TEST_F(PaymentCardTest, ValidCard) {
    EXPECT_TRUE(card->isValidCard());
}
