#include <gtest/gtest.h>
#include "Passport.h"
class PassportTest : public ::testing::Test {
protected:
    Visa* visa; Passport* passport;
    time_t now; time_t issueDate; time_t expiryDate;

    void SetUp() override {
        now = time(nullptr);
        issueDate = now - 86400 * 100;
        expiryDate = now + 86400 * 365;

        visa = new Visa("V123", "France", issueDate, expiryDate, VisaType::Tourist);
        passport = new Passport("P987654", "Russia", "Ivan Ivanov", issueDate, expiryDate, *visa, MaritalStatus::NotMarried);
    }

    void TearDown() override {
        delete visa; delete passport;
    }
};

TEST_F(PassportTest, ConstructorInitializesAllFieldsCorrectly) {
    EXPECT_EQ(passport->getPassportNumber(), "P987654");
    EXPECT_EQ(passport->getCountry(), "Russia");
    EXPECT_EQ(passport->getHolderName(), "Ivan Ivanov");
    EXPECT_EQ(passport->getIssueDate(), issueDate);
    EXPECT_EQ(passport->getExpiryDate(), expiryDate);
    EXPECT_EQ(passport->getMaritalStatus(), MaritalStatus::NotMarried);

    const Visa& v = passport->getVisa();
    EXPECT_EQ(v.getVisaNumber(), "V123");
    EXPECT_EQ(v.getCountry(), "France");
    EXPECT_EQ(v.getType(), VisaType::Tourist);
}

TEST_F(PassportTest, SettersUpdateAllFieldsCorrectly) {
    time_t newIssue = now - 86400 * 200;
    time_t newExpiry = now + 86400 * 700;
    Visa newVisa("V999", "Germany", newIssue, newExpiry, VisaType::Business);

    passport->setPassportNumber("P111222");
    passport->setCountry("Germany");
    passport->setHolderName("Petrov Petr");
    passport->setIssueDate(newIssue);
    passport->setExpiryDate(newExpiry);
    passport->setVisa(newVisa);
    passport->setMaritalStatus(MaritalStatus::Married);

    EXPECT_EQ(passport->getPassportNumber(), "P111222");
    EXPECT_EQ(passport->getCountry(), "Germany");
    EXPECT_EQ(passport->getHolderName(), "Petrov Petr");
    EXPECT_EQ(passport->getIssueDate(), newIssue);
    EXPECT_EQ(passport->getExpiryDate(), newExpiry);
    EXPECT_EQ(passport->getMaritalStatus(), MaritalStatus::Married);
    EXPECT_EQ(passport->getVisa().getCountry(), "Germany");
    EXPECT_EQ(passport->getVisa().getType(), VisaType::Business);
}

TEST_F(PassportTest, RenewExtendsExpiryDateWhenNewDateIsLater) {
    time_t newExpiry = expiryDate + 86400 * 100;
    passport->renew(newExpiry);
    EXPECT_EQ(passport->getExpiryDate(), newExpiry);
}

TEST_F(PassportTest, RenewDoesNotChangeExpiryDateWhenEarlier) {
    time_t oldExpiry = passport->getExpiryDate();
    passport->renew(expiryDate - 86400 * 10);
    EXPECT_EQ(passport->getExpiryDate(), oldExpiry);
}

TEST_F(PassportTest, ChangeMaritalStatusUpdatesAndReturnsNewStatus) {
    MaritalStatus newStatus = passport->changeMaritalStatus(MaritalStatus::Divorced);
    EXPECT_EQ(newStatus, MaritalStatus::Divorced);
    EXPECT_EQ(passport->getMaritalStatus(), MaritalStatus::Divorced);
}
