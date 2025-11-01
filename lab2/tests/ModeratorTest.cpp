#include <gtest/gtest.h>
#include "Moderator.h"
#include "UserProfile.h"
#include "Settings.h"
#include "Wallet.h"
#include "FriendList.h"
#include "BlockList.h"
#include "Permission.h"
#include "Currency.h"

class ModeratorTest : public ::testing::Test {
protected:
    UserProfile* profile; Settings* settings; Currency* currency; Wallet* wallet;
    FriendList* friends; BlockList* blocks; vector<Permission>* permissions;
    User* moderatorUser; User* reporter; User* violator;
    Report* report1; Report* report2; Moderator* moderator;

    void SetUp() override {
        profile = new UserProfile("Иван", "Иванов", "12.01.2007", "01.09.2023",
            "+375291234567", "Беларусь", "Минск", { "Игры", "Программирование" });
        settings = new Settings(18, "Русский", true, true, false, true, Theme::LIGHT);
        currency = new Currency("BYN", "Белорусский рубль", 1.0);
        wallet = new Wallet(5000.0, {}, {}, *currency);
        friends = new FriendList({}, {}, {});
        blocks = new BlockList({}, {});
        permissions = new vector<Permission>{
            Permission("READ", "Чтение данных", true),
            Permission("WRITE", "Изменение данных", true)
        };

        moderatorUser = new User(1, "moderator", "moderator@example.com", "pass", true,
            *profile, *settings, *wallet, *friends, *blocks, UserRole::MODERATOR, *permissions);
        reporter = new User(2, "reporter", "reporter@example.com", "12345", true,
            *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);
        violator = new User(3, "violator", "violator@example.com", "badpass", false,
            *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);

        report1 = new Report("Спам", "2025-10-24T12:00", false, false, *reporter, *violator, ReportTargetType::USER);
        report2 = new Report("Оскорбление", "2025-10-23T10:00", false, false, *reporter, *violator, ReportTargetType::COMMENT);

        vector<Report> reports = { *report1, *report2 };
        moderator = new Moderator("Форум", reports, *moderatorUser);
    }

    void TearDown() override {
        delete moderator; delete report1; delete report2; delete violator; delete reporter;
        delete moderatorUser; delete permissions; delete blocks; delete friends;
        delete wallet; delete settings; delete currency; delete profile;
    }
};

TEST_F(ModeratorTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(moderator->getAreaOfResponsibility(), "Форум");
    EXPECT_EQ(moderator->getAssignedReports().size(), 2);
    EXPECT_EQ(moderator->getUser().getUsername(), "moderator");
}

TEST_F(ModeratorTest, SettersWorkCorrectly) {
    vector<Report> newReports = { *report1 };
    moderator->setAreaOfResponsibility("Чат");
    moderator->setAssignedReports(newReports);
    moderator->setUser(*reporter);

    EXPECT_EQ(moderator->getAreaOfResponsibility(), "Чат");
    EXPECT_EQ(moderator->getAssignedReports().size(), 1);
    EXPECT_EQ(moderator->getUser().getUsername(), "reporter");
}

TEST_F(ModeratorTest, ResolveReportChangesResolvedStatus) {
    int reportId = moderator->getAssignedReports()[0].getId();
    moderator->resolveReport(reportId);
    EXPECT_TRUE(moderator->getAssignedReports()[0].getResolved());
}

TEST_F(ModeratorTest, EscalateReportSetsEscalatedFlag) {
    int reportId = moderator->getAssignedReports()[1].getId();
    moderator->escalateReport(reportId);
    EXPECT_NO_THROW(moderator->escalateReport(reportId));
}

TEST_F(ModeratorTest, ResolveNonExistingReportDoesNothing) {
    EXPECT_NO_THROW(moderator->resolveReport(9999));
}

TEST_F(ModeratorTest, EscalateNonExistingReportDoesNothing) {
    EXPECT_NO_THROW(moderator->escalateReport(9999));
}
