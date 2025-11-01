#include <gtest/gtest.h>
#include "ExchangeRate.h"

class ExchangeRateTest : public ::testing::Test {
protected:
    ExchangeRate* rate;
    time_t lastUpdated;

    void SetUp() override {
        lastUpdated = time(nullptr) - 3600;
        rate = new ExchangeRate("USD", "EUR", 0.92, lastUpdated);
    }

    void TearDown() override {
        delete rate;
    }
};

TEST_F(ExchangeRateTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(rate->getBaseCurrency(), "USD");
    EXPECT_EQ(rate->getTargetCurrency(), "EUR");
    EXPECT_DOUBLE_EQ(rate->getRate(), 0.92);
    EXPECT_EQ(rate->getLastUpdated(), lastUpdated);
}

TEST_F(ExchangeRateTest, SettersWorkCorrectly) {
    time_t newTime = time(nullptr);
    rate->setBaseCurrency("RUB");
    rate->setTargetCurrency("GBP");
    rate->setRate(0.011);
    rate->setLastUpdated(newTime);

    EXPECT_EQ(rate->getBaseCurrency(), "RUB");
    EXPECT_EQ(rate->getTargetCurrency(), "GBP");
    EXPECT_DOUBLE_EQ(rate->getRate(), 0.011);
    EXPECT_EQ(rate->getLastUpdated(), newTime);
}

TEST_F(ExchangeRateTest, ConvertReturnsCorrectValue) {
    double result = rate->convert(100.0);
    EXPECT_DOUBLE_EQ(result, 92.0);
}

TEST_F(ExchangeRateTest, ConvertReturnsZeroForNegativeAmount) {
    EXPECT_DOUBLE_EQ(rate->convert(-50.0), 0.0);
}

TEST_F(ExchangeRateTest, UpdateRateChangesRateAndTime) {
    double newRate = 1.05;
    rate->updateRate(newRate);
    EXPECT_DOUBLE_EQ(rate->getRate(), 1.05);
    EXPECT_NEAR(difftime(time(nullptr), rate->getLastUpdated()), 0, 2);
}

TEST_F(ExchangeRateTest, UpdateRateThrowsIfNegative) {
    EXPECT_THROW(rate->updateRate(-0.5), InvadRateException);
    EXPECT_THROW(rate->updateRate(0.0), InvadRateException);
}
