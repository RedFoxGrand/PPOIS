#include "gtest/gtest.h"
#include "LoyaltyProgram.h"

class LoyaltyProgramTest : public ::testing::Test {
protected:
    ContactInfo* contact; Visa* visa; Passport* passport;
    Passenger* passenger; LoyaltyProgram* program; time_t now;

    void SetUp() override {
        now = time(nullptr);

        contact = new ContactInfo("ivanov@example.com", "+79998887766", "Россия, Москва");
        visa = new Visa("V001", "Германия", now - 200000, now + 500000, VisaType::Tourist);
        passport = new Passport("PP123456", "Россия", "Сергей Иванов", now - 600000, now + 800000, *visa, MaritalStatus::Married);
        passenger = new Passenger("Сергей", "Иванов", now - 1000000000, *contact, "P001", *passport);

        program = new LoyaltyProgram("LP001", *passenger, 5000, TierType::Silver, now);
    }

    void TearDown() override {
        delete contact; delete visa;  delete passport; delete passenger; delete program;
    }
};

TEST_F(LoyaltyProgramTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(program->getProgramId(), "LP001");
    EXPECT_EQ(program->getMember().getPassengerId(), "P001");
    EXPECT_EQ(program->getMiles(), 5000);
    EXPECT_EQ(program->getTierType(), TierType::Silver);
    EXPECT_EQ(program->getJoinDate(), now);
}

TEST_F(LoyaltyProgramTest, SettersWorkCorrectly) {
    time_t newTime = now - 10000;
    program->setProgramId("LP002");
    program->setMiles(7500);
    program->setTierType(TierType::Gold);
    program->setJoinDate(newTime);

    EXPECT_EQ(program->getProgramId(), "LP002");
    EXPECT_EQ(program->getMiles(), 7500);
    EXPECT_EQ(program->getTierType(), TierType::Gold);
    EXPECT_EQ(program->getJoinDate(), newTime);
}

TEST_F(LoyaltyProgramTest, SetMemberUpdatesMemberInfo) {
    ContactInfo contact2("petrov@example.com", "+79995556677", "Россия, Санкт-Петербург");
    Visa visa2("V002", "Франция", now - 300000, now + 600000, VisaType::Business);
    Passport passport2("PP654321", "Россия", "Андрей Петров", now - 700000, now + 900000, visa2, MaritalStatus::NotMarried);
    Passenger passenger2("Андрей", "Петров", now - 1200000000, contact2, "P002", passport2);

    program->setMember(passenger2);
    EXPECT_EQ(program->getMember().getPassengerId(), "P002");
    EXPECT_EQ(program->getMember().getFullName(), "Андрей Петров");
}

TEST_F(LoyaltyProgramTest, AddMilesIncreasesValueWhenPositive) {
    program->addMiles(1500);
    EXPECT_EQ(program->getMiles(), 6500);
}

TEST_F(LoyaltyProgramTest, AddMilesDoesNothingWhenNegative) {
    program->addMiles(-2000);
    EXPECT_EQ(program->getMiles(), 5000);
}

TEST_F(LoyaltyProgramTest, RedeemMilesReducesBalanceWhenEnoughMiles) {
    bool success = program->redeemMiles(3000);
    EXPECT_TRUE(success);
    EXPECT_EQ(program->getMiles(), 2000);
}

TEST_F(LoyaltyProgramTest, RedeemMilesFailsWhenNotEnoughMiles) {
    bool success = program->redeemMiles(10000);
    EXPECT_FALSE(success);
    EXPECT_EQ(program->getMiles(), 5000);
}

TEST_F(LoyaltyProgramTest, RedeemMilesFailsWhenAmountIsZeroOrNegative) {
    EXPECT_FALSE(program->redeemMiles(0));
    EXPECT_FALSE(program->redeemMiles(-500));
    EXPECT_EQ(program->getMiles(), 5000);
}

TEST_F(LoyaltyProgramTest, UpgradeTierChangesTierWhenHigher) {
    program->upgradeTier(TierType::Gold);
    EXPECT_EQ(program->getTierType(), TierType::Gold);

    program->upgradeTier(TierType::Platinum);
    EXPECT_EQ(program->getTierType(), TierType::Platinum);
}

TEST_F(LoyaltyProgramTest, UpgradeTierDoesNothingWhenLowerOrEqual) {
    program->setTierType(TierType::Gold);
    program->upgradeTier(TierType::Silver); 
    EXPECT_EQ(program->getTierType(), TierType::Gold);

    program->upgradeTier(TierType::Gold); 
    EXPECT_EQ(program->getTierType(), TierType::Gold);
}
