#include <gtest/gtest.h>
#include "Fare.h"

TEST(FareTest, ConstructorAndGettersWorkCorrectly) {
    Fare fare("EC100", 15000.0, FareClass::Economy, "НДС", "Без скидок");

    EXPECT_EQ(fare.getFareCode(), "EC100");
    EXPECT_DOUBLE_EQ(fare.getPrice(), 15000.0);
    EXPECT_EQ(fare.getFareClass(), FareClass::Economy);
    EXPECT_EQ(fare.getTax(), "НДС");
    EXPECT_EQ(fare.getDiscounts(), "Без скидок");
}

TEST(FareTest, SettersChangeValuesCorrectly) {
    Fare fare("EC200", 20000.0, FareClass::Business, "НДС", "Нет");
    fare.setFareCode("FC500");
    fare.setPrice(25000.0);
    fare.setFareClass(FareClass::FirstClass);
    fare.setTax("Налог включён");
    fare.setDiscounts("10%");

    EXPECT_EQ(fare.getFareCode(), "FC500");
    EXPECT_DOUBLE_EQ(fare.getPrice(), 25000.0);
    EXPECT_EQ(fare.getFareClass(), FareClass::FirstClass);
    EXPECT_EQ(fare.getTax(), "Налог включён");
    EXPECT_EQ(fare.getDiscounts(), "10%");
}

TEST(FareTest, CalculateTotalWorksCorrectly) {
    Fare fare("EC300", 10000.0, FareClass::Economy, "НДС", "");
    double total = fare.calculateTotal(20.0);  // 20% налог
    EXPECT_DOUBLE_EQ(total, 12000.0);
}

TEST(FareTest, ApplyDiscountReducesPriceCorrectly) {
    Fare fare("EC400", 20000.0, FareClass::PremiumEconomy, "НДС", "5%");
    fare.applyDiscount(10.0);  // скидка 10%
    EXPECT_NEAR(fare.getPrice(), 18000.0, 0.001);
}

TEST(FareTest, ApplyDiscountDoesNothingIfInvalid) {
    Fare fare("EC500", 15000.0, FareClass::Economy, "НДС", "");
    fare.applyDiscount(0.0);
    EXPECT_DOUBLE_EQ(fare.getPrice(), 15000.0);
    fare.applyDiscount(150.0);
    EXPECT_DOUBLE_EQ(fare.getPrice(), 15000.0);
}

TEST(FareTest, RefundableFaresReturnTrueOnlyForBusinessAndFirstClass) {
    Fare fareEconomy("E100", 10000.0, FareClass::Economy, "НДС", "");
    Fare fareBusiness("B200", 20000.0, FareClass::Business, "НДС", "");
    Fare fareFirst("F300", 30000.0, FareClass::FirstClass, "НДС", "");

    EXPECT_FALSE(fareEconomy.isRefundable());
    EXPECT_TRUE(fareBusiness.isRefundable());
    EXPECT_TRUE(fareFirst.isRefundable());
}
