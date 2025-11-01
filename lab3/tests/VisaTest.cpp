#include <gtest/gtest.h>
#include "Visa.h"

using namespace std;

class VisaTest : public ::testing::Test {
protected:
    Visa* visa; time_t now; time_t issueDate; time_t expiryDate;

    void SetUp() override {
        now = time(nullptr);
        issueDate = now - 60 * 60 * 24 * 30; 
        expiryDate = now + 60 * 60 * 24 * 30;
        visa = new Visa("A123456", "ßïîíèÿ", issueDate, expiryDate, VisaType::Tourist);
    }

    void TearDown() override {
        delete visa;
    }
};

TEST_F(VisaTest, ConstructorInitializesValuesCorrectly) {
    EXPECT_EQ(visa->getVisaNumber(), "A123456");
    EXPECT_EQ(visa->getCountry(), "ßïîíèÿ");
    EXPECT_EQ(visa->getType(), VisaType::Tourist);
    EXPECT_EQ(visa->getIssueDate(), issueDate);
    EXPECT_EQ(visa->getExpiryDate(), expiryDate);
}

TEST_F(VisaTest, SettersWorkCorrectly) {
    time_t newIssue = now - 60 * 60 * 24 * 60;
    time_t newExpiry = now + 60 * 60 * 24 * 60;

    visa->setVisaNumber("B987654");
    visa->setCountry("ÑØÀ");
    visa->setIssueDate(newIssue);
    visa->setExpiryDate(newExpiry);
    visa->setType(VisaType::Work);

    EXPECT_EQ(visa->getVisaNumber(), "B987654");
    EXPECT_EQ(visa->getCountry(), "ÑØÀ");
    EXPECT_EQ(visa->getType(), VisaType::Work);
    EXPECT_EQ(visa->getIssueDate(), newIssue);
    EXPECT_EQ(visa->getExpiryDate(), newExpiry);
}

TEST_F(VisaTest, IsExpiredReturnsFalseWhenNotExpired) {
    EXPECT_FALSE(visa->isExpired());
}

TEST_F(VisaTest, IsExpiredReturnsTrueWhenExpired) {
    time_t pastExpiry = now - 60 * 60 * 24 * 10;
    visa->setExpiryDate(pastExpiry);
    EXPECT_TRUE(visa->isExpired());
}

TEST_F(VisaTest, RenewExtendsExpiryCorrectly) {
    time_t newExpiry = expiryDate + 60 * 60 * 24 * 90; 
    visa->renew(newExpiry);
    EXPECT_EQ(visa->getExpiryDate(), newExpiry);
}

TEST_F(VisaTest, RenewThrowsExceptionWhenNewExpiryIsEarlier) {
    time_t earlier = expiryDate - 60 * 60 * 24 * 5; 
    EXPECT_THROW(visa->renew(earlier), ExpiredException);
}
