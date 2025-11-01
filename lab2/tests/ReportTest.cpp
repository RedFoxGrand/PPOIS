#include <gtest/gtest.h>
#include "Report.h"
#include "UserProfile.h"
#include "Settings.h"
#include "Wallet.h"
#include "FriendList.h"
#include "BlockList.h"
#include "Permission.h"
#include "Currency.h"

class ReportTest : public ::testing::Test {
protected:
    UserProfile* profile; Settings* settings; Currency* currency; Wallet* wallet; FriendList* friends; BlockList* blocks; vector<Permission>* permissions; User* reporter; User* target; Report* report;

    void SetUp() override {
        profile = new UserProfile("Иван", "Иванов", "12.01.2007", "01.09.2023", "+375291234567", "Беларусь", "Минск", { "Игры", "Программирование" });
        settings = new Settings(18, "Русский", true, true, false, true, Theme::LIGHT);
        currency = new Currency("BYN", "Белорусский рубль", 1.0);
        wallet = new Wallet(5000.0, {}, {}, *currency);
        friends = new FriendList({}, {}, {});
        blocks = new BlockList({}, {});
        permissions = new vector<Permission>{ Permission("READ", "Чтение данных", true), Permission("WRITE", "Изменение данных", true) };

        reporter = new User(1, "reporter", "reporter@example.com", "pass", true, *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);
        target = new User(2, "target", "target@example.com", "12345", false, *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);
        report = new Report("Спам", "2025-10-24 12:00:00", false, false, *reporter, *target, ReportTargetType::USER);
    }

    void TearDown() override {
        delete report; delete target; delete reporter; delete permissions; delete blocks; delete friends; delete wallet; delete settings; delete currency; delete profile;
    }
};

TEST_F(ReportTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(report->getReason(), "Спам");
    EXPECT_EQ(report->getTimestamp(), "2025-10-24 12:00:00");
    EXPECT_FALSE(report->getResolved());
    EXPECT_EQ(report->getReporter().getUsername(), "reporter");
    EXPECT_EQ(report->getTarget().getUsername(), "target");
    EXPECT_EQ(report->getTargetType(), ReportTargetType::USER);
}

TEST_F(ReportTest, SettersUpdateFieldsCorrectly) {
    report->setReason("Оскорбление");
    report->setTimestamp("2025-10-23 10:00:00");
    report->setResolved(true);
    report->setTargetType(ReportTargetType::COMMENT);
    report->setReporter(*target);
    report->setTarget(*reporter);

    EXPECT_EQ(report->getReason(), "Оскорбление");
    EXPECT_EQ(report->getTimestamp(), "2025-10-23 10:00:00");
    EXPECT_TRUE(report->getResolved());
    EXPECT_EQ(report->getTargetType(), ReportTargetType::COMMENT);
    EXPECT_EQ(report->getReporter().getUsername(), "target");
    EXPECT_EQ(report->getTarget().getUsername(), "reporter");
}

TEST_F(ReportTest, GetIdReturnsTargetId) {
    EXPECT_EQ(report->getId(), 2);
}

TEST_F(ReportTest, MarkAsResolvedChangesResolvedStatusAndTimestamp) {
    report->markAsResolved();
    EXPECT_TRUE(report->getResolved());
    EXPECT_NE(report->getTimestamp(), "2025-10-24 12:00:00");
}

TEST_F(ReportTest, MarkAsResolvedTwiceDoesNotChangeTimestamp) {
    report->markAsResolved();
    string ts1 = report->getTimestamp();
    report->markAsResolved();
    EXPECT_EQ(report->getTimestamp(), ts1);
}

TEST_F(ReportTest, SetEscalatedUpdatesTimestampWhenChangingState) {
    string tsBefore = report->getTimestamp();
    report->setEscalated(true);
    EXPECT_NE(report->getTimestamp(), tsBefore);
}

TEST_F(ReportTest, SetEscalatedNoChangeDoesNotAffectTimestamp) {
    report->setEscalated(true);
    string ts1 = report->getTimestamp();
    report->setEscalated(true);
    EXPECT_EQ(report->getTimestamp(), ts1);
}
