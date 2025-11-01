#include <gtest/gtest.h>
#include "Ban.h"
#include "User.h"
#include "UserProfile.h"
#include "Settings.h"
#include "Wallet.h"
#include "FriendList.h"
#include "BlockList.h"
#include "Permission.h"
#include "Currency.h"

class BanTest : public ::testing::Test {
protected:
    UserProfile* profile;
    Settings* settings;
    Currency* currency;
    Wallet* wallet;
    FriendList* friends;
    BlockList* blocks;
    vector<Permission>* permissions;
    User* user;
    Ban* banFull;
    Ban* banSimple;

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

        user = new User(1, "alice", "alice@example.com", "alicepass", true,
            *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);

        banFull = new Ban("Токсичное поведение", "01.01.2025", "31.12.2025", *user);
        banSimple = new Ban("Оскорбления", *user);
    }

    void TearDown() override {
        delete banFull; delete banSimple; delete user; delete permissions;delete blocks;
        delete friends; delete wallet; delete settings; delete currency; delete profile;
    }
};

TEST_F(BanTest, ConstructorWithAllFieldsInitializesCorrectly) {
    EXPECT_EQ(banFull->getReason(), "Токсичное поведение");
    EXPECT_EQ(banFull->getStartDate(), "01.01.2025");
    EXPECT_EQ(banFull->getEndDate(), "31.12.2025");
    EXPECT_EQ(banFull->getBannedUser().getUsername(), "alice");
}

TEST_F(BanTest, ConstructorWithDefaultDatesInitializesCorrectly) {
    EXPECT_EQ(banSimple->getReason(), "Оскорбления");
    EXPECT_EQ(banSimple->getStartDate(), "now");
    EXPECT_EQ(banSimple->getEndDate(), "0");
    EXPECT_EQ(banSimple->getBannedUser().getUsername(), "alice");
}

TEST_F(BanTest, SettersUpdateValuesCorrectly) {
    User* bob = new User(1, "bob", "bob@example.com", "qwerty", false,
        *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);

    banFull->setReason("Спам");
    banFull->setStartDate("01.05.2025");
    banFull->setEndDate("01.10.2025");
    banFull->setBannedUser(*bob);

    EXPECT_EQ(banFull->getReason(), "Спам");
    EXPECT_EQ(banFull->getStartDate(), "01.05.2025");
    EXPECT_EQ(banFull->getEndDate(), "01.10.2025");
    EXPECT_EQ(banFull->getBannedUser().getUsername(), "bob");

    delete bob;
}

TEST_F(BanTest, IsActiveReturnsTrueWhenEndDateIsZero) {
    EXPECT_TRUE(banSimple->isActive());
}

TEST_F(BanTest, IsActiveReturnsFalseWhenEndDateIsNotZero) {
    EXPECT_FALSE(banFull->isActive());
}

TEST_F(BanTest, LiftBanDoesNotChangeNonActiveBan) {
    string oldEndDate = banFull->getEndDate();
    banFull->liftBan();
    EXPECT_EQ(banFull->getEndDate(), oldEndDate);
}

TEST_F(BanTest, LiftBanSetsEndDateToZeroForActiveBan) {
    banSimple->liftBan();
    EXPECT_EQ(banSimple->getEndDate(), "0");
}
