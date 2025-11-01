#include <gtest/gtest.h>
#include "Subscription.h"
#include "Exception.h"

using namespace std;

class SubscriptionTest : public ::testing::Test {
protected:
    Subscription* sub;

    void SetUp() override {
        sub = new Subscription("Premium", "2025-01-01", "2026-01-01", 9.99, true, true);
    }

    void TearDown() override {
        delete sub;
    }
};

TEST_F(SubscriptionTest, ConstructorAndGetters) {
    EXPECT_EQ(sub->getPlanName(), "Premium");
    EXPECT_EQ(sub->getStartDate(), "2025-01-01");
    EXPECT_EQ(sub->getEndDate(), "2026-01-01");
    EXPECT_DOUBLE_EQ(sub->getMonthlyCost(), 9.99);
    EXPECT_TRUE(sub->getIsActive());
    EXPECT_TRUE(sub->getAutoRenew());
}

TEST_F(SubscriptionTest, SettersWorkCorrectly) {
    sub->setPlanName("Basic");
    sub->setStartDate("2024-10-01");
    sub->setEndDate("2025-10-01");
    sub->setMonthlyCost(4.99);
    sub->setIsActive(false);
    sub->setAutoRenew(false);

    EXPECT_EQ(sub->getPlanName(), "Basic");
    EXPECT_EQ(sub->getStartDate(), "2024-10-01");
    EXPECT_EQ(sub->getEndDate(), "2025-10-01");
    EXPECT_DOUBLE_EQ(sub->getMonthlyCost(), 4.99);
    EXPECT_FALSE(sub->getIsActive());
    EXPECT_FALSE(sub->getAutoRenew());
}

TEST_F(SubscriptionTest, RenewSubscriptionSuccessful) {
    testing::internal::CaptureStdout();
    sub->renewSubscription("2027-01-01");
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(sub->getEndDate(), "2027-01-01");
}

TEST_F(SubscriptionTest, RenewSubscriptionAutoRenewOff) {
    sub->setAutoRenew(false);
    EXPECT_THROW(sub->renewSubscription("2027-01-01"), SubscriptionExpiredException);
}

TEST_F(SubscriptionTest, RenewSubscriptionInactive) {
    sub->setIsActive(false);
    EXPECT_THROW(sub->renewSubscription("2027-01-01"), SubscriptionExpiredException);
}

TEST_F(SubscriptionTest, IsExpiredReturnsFalseWhenActive) {
    EXPECT_FALSE(sub->isExpired());
}

TEST_F(SubscriptionTest, IsExpiredReturnsTrueWhenInactive) {
    sub->setIsActive(false);
    EXPECT_TRUE(sub->isExpired());
}
