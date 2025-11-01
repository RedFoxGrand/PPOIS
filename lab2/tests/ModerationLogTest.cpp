#include <gtest/gtest.h>
#include "ModerationLog.h"
#include "UserProfile.h"
#include "Settings.h"
#include "Wallet.h"
#include "FriendList.h"
#include "BlockList.h"
#include "Permission.h"
#include "Currency.h"

using namespace std;

class ModerationLogTest : public ::testing::Test {
protected:
    UserProfile* profile; Settings* settings; Currency* currency; Wallet* wallet;
    FriendList* friends; BlockList* blocks; vector<Permission>* permissions;
    User* moderator; User* target; ModerationLog* log;

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

        moderator = new User(1, "moderator", "mod@example.com", "pass123", true,
            *profile, *settings, *wallet, *friends, *blocks, UserRole::MODERATOR, *permissions);
        target = new User(2, "target", "target@example.com", "12345", false,
            *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);
        log = new ModerationLog("Ban", "Нарушение правил", "2025-10-24 13:00:00", *moderator, *target);
    }

    void TearDown() override {
        delete log; delete target; delete moderator; delete permissions; delete blocks;
        delete friends; delete wallet; delete settings; delete currency; delete profile;
    }
};

TEST_F(ModerationLogTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(log->getAction(), "Ban");
    EXPECT_EQ(log->getReason(), "Нарушение правил");
    EXPECT_EQ(log->getTimestamp(), "2025-10-24 13:00:00");
    EXPECT_EQ(log->getModerator().getUsername(), "moderator");
    EXPECT_EQ(log->getTarget().getUsername(), "target");
}

TEST_F(ModerationLogTest, SettersWorkCorrectly) {
    log->setAction("Mute"); log->setReason("Спам"); log->setTimestamp("2025-10-25 12:00:00");
    log->setModerator(*target); log->setTarget(*moderator);

    EXPECT_EQ(log->getAction(), "Mute");
    EXPECT_EQ(log->getReason(), "Спам");
    EXPECT_EQ(log->getTimestamp(), "2025-10-25 12:00:00");
    EXPECT_EQ(log->getModerator().getUsername(), "target");
    EXPECT_EQ(log->getTarget().getUsername(), "moderator");
}

TEST_F(ModerationLogTest, RecordActionUpdatesFields) {
    log->recordAction("Warn", "Оскорбление других пользователей");
    EXPECT_EQ(log->getAction(), "Warn");
    EXPECT_EQ(log->getReason(), "Оскорбление других пользователей");
}

TEST_F(ModerationLogTest, RecordActionDoesNotUpdateIfEmpty) {
    string prevAction = log->getAction(), prevReason = log->getReason();
    log->recordAction("", "Причина без действия");
    EXPECT_EQ(log->getAction(), prevAction);
    EXPECT_EQ(log->getReason(), prevReason);
    log->recordAction("Kick", "");
    EXPECT_EQ(log->getAction(), prevAction);
    EXPECT_EQ(log->getReason(), prevReason);
}

TEST_F(ModerationLogTest, TimestampIsStoredCorrectly) {
    EXPECT_EQ(log->getTimestamp(), "2025-10-24 13:00:00");
}
