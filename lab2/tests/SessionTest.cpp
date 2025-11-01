#include <gtest/gtest.h>
#include "Session.h"
#include "UserProfile.h"
#include "Settings.h"
#include "Wallet.h"
#include "FriendList.h"
#include "BlockList.h"
#include "Permission.h"
#include "Currency.h"

using namespace std;

class SessionTest : public ::testing::Test {
protected:
    UserProfile* profile; Settings* settings; Currency* currency; Wallet* wallet;
    FriendList* friends; BlockList* blocks; vector<Permission>* permissions; User* user; Session* session;

    void SetUp() override {
        profile = new UserProfile("Иван", "Иванов", "12.01.2007", "01.09.2023",
            "+375291234567", "Беларусь", "Минск", { "Игры", "Программирование" });
        settings = new Settings(18, "Русский", true, true, false, true, Theme::LIGHT);
        currency = new Currency("BYN", "Белорусский рубль", 1.0);
        wallet = new Wallet(1500.0, {}, {}, *currency);
        friends = new FriendList({}, {}, {});
        blocks = new BlockList({}, {});
        permissions = new vector<Permission>{
            Permission("READ", "Чтение данных", true),
            Permission("WRITE", "Изменение данных", true)
        };

        user = new User(1, "ivan", "ivan@example.com", "pass123", true,
            *profile, *settings, *wallet, *friends, *blocks,
            UserRole::USER, *permissions);

        session = new Session("abc123", "2025-01-01 10:00:00", "3600", *user);
    }

    void TearDown() override {
        delete session; delete user; delete permissions; delete blocks;
        delete friends; delete wallet; delete settings; delete currency; delete profile;
    }
};

TEST_F(SessionTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(session->getToken(), "abc123");
    EXPECT_EQ(session->getCreatedDate(), "2025-01-01 10:00:00");
    EXPECT_EQ(session->getDuration(), "3600");
    EXPECT_EQ(session->getUser().getUsername(), "ivan");
}

TEST_F(SessionTest, SettersWorkCorrectly) {
    User newUser(2, "alex", "alex@example.com", "pass456", false,
        *profile, *settings, *wallet, *friends, *blocks,
        UserRole::MODERATOR, *permissions);

    session->setToken("xyz789");
    session->setCreatedDate("2025-02-02 12:00:00");
    session->setDuration("7200");
    session->setUser(newUser);

    EXPECT_EQ(session->getToken(), "xyz789");
    EXPECT_EQ(session->getCreatedDate(), "2025-02-02 12:00:00");
    EXPECT_EQ(session->getDuration(), "7200");
    EXPECT_EQ(session->getUser().getUsername(), "alex");
}

TEST_F(SessionTest, IsValidSessionReturnsTrueForValidTokenAndDuration) {
    EXPECT_TRUE(session->isValidSession());
}

TEST_F(SessionTest, IsValidSessionThrowsIfTokenEmpty) {
    session->setToken("");
    EXPECT_THROW(session->isValidSession(), SessionExpiredException);
}

TEST_F(SessionTest, ExtendDurationAppendsExtension) {
    string before = session->getDuration();
    session->extendDuration();
    EXPECT_NE(session->getDuration(), before);
    EXPECT_TRUE(session->getDuration().find("3600") != string::npos);
}

TEST_F(SessionTest, ExtendDurationThrowsIfTokenEmpty) {
    session->setToken("");
    EXPECT_THROW(session->extendDuration(), SessionExpiredException);
}

TEST_F(SessionTest, InvalidateSessionClearsTokenAndDuration) {
    session->invalidateSession();
    EXPECT_TRUE(session->getToken().empty());
    EXPECT_TRUE(session->getDuration().empty());
}

TEST_F(SessionTest, InvalidateSessionThrowsIfAlreadyInvalidated) {
    session->setToken("");
    EXPECT_THROW(session->invalidateSession(), SessionExpiredException);
}
