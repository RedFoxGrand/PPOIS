#include <gtest/gtest.h>
#include "Currency.h"

using namespace std;

class CurrencyTest : public ::testing::Test {
protected:
    Currency* byn;
    Currency* usd;

    void SetUp() override {
        byn = new Currency("BYN", "Белорусский рубль", 0.31);
        usd = new Currency("USD", "Доллар США", 1.0);
    }

    void TearDown() override {
        delete byn;
        delete usd;
    }
};

TEST_F(CurrencyTest, ConstructorAndGetters) {
    EXPECT_EQ(byn->getCode(), "BYN");
    EXPECT_EQ(byn->getName(), "Белорусский рубль");
    EXPECT_DOUBLE_EQ(byn->getExchangeRateToUsd(), 0.31);
}

TEST_F(CurrencyTest, SettersChangeValues) {
    byn->setCode("EUR");
    byn->setName("Евро");
    byn->setExchangeRateToUsd(1.1);

    EXPECT_EQ(byn->getCode(), "EUR");
    EXPECT_EQ(byn->getName(), "Евро");
    EXPECT_DOUBLE_EQ(byn->getExchangeRateToUsd(), 1.1);
}

TEST_F(CurrencyTest, ConvertToUsdToOtherCurrency) {
    double amount = 100.0;
    double converted = byn->convertToUSD(amount, *usd);
    EXPECT_DOUBLE_EQ(converted, 31.0);
}

TEST_F(CurrencyTest, ConvertUsdToByn) {
    double amount = 50.0;
    double converted = usd->convertToUSD(amount, *byn);
    EXPECT_NEAR(converted, 161.29, 0.01);
}

TEST_F(CurrencyTest, ConvertWithZeroExchangeRate) {
    Currency zeroCurrency("ZRO", "Zero Currency", 0.0);

    testing::internal::CaptureStderr();
    double result = byn->convertToUSD(100.0, zeroCurrency);
    string output = testing::internal::GetCapturedStderr();

    EXPECT_DOUBLE_EQ(result, 0.0);
}
