#include <gtest/gtest.h>
#include "BlockList.h"
#include "User.h"
#include "UserProfile.h"
#include "Settings.h"
#include "Wallet.h"
#include "FriendList.h"
#include "Permission.h"
#include "Currency.h"

class BlockListTest : public ::testing::Test {
protected:
    UserProfile* profile; Settings* settings; Currency* currency; Wallet* wallet;
    FriendList* friends; BlockList* blocks; vector<Permission>* permissions;
    User* user1; User* user2;

    void SetUp() override {
        profile = new UserProfile("Иван", "Иванов", "12.01.2007", "01.09.2023",
            "+375291234567", "Беларусь", "Минск", { "Музыка", "Спорт" });
        settings = new Settings(18, "Русский", true, true, false, true, Theme::LIGHT);
        currency = new Currency("BYN", "Белорусский рубль", 1.0);
        wallet = new Wallet(1000.0, {}, {}, *currency);
        friends = new FriendList({}, {}, {});
        blocks = new BlockList({}, {});
        permissions = new vector<Permission>{
            Permission("READ", "Чтение данных", true),
            Permission("WRITE", "Изменение данных", true)
        };
        user1 = new User(1, "ivan", "ivan@mail.ru", "1234", true,
            *profile, *settings, *wallet, *friends, *blocks,
            UserRole::USER, *permissions);
        user2 = new User(2, "petr", "petr@mail.ru", "5678", true,
            *profile, *settings, *wallet, *friends, *blocks,
            UserRole::USER, *permissions);
    }

    void TearDown() override {
        delete user1; delete user2; delete permissions; delete blocks;
        delete friends; delete wallet; delete settings; delete currency; delete profile;
    }
};

TEST_F(BlockListTest, ConstructorInitializesData) {
    EXPECT_TRUE(blocks->getBlockedUsers().empty());
    EXPECT_TRUE(blocks->getBlockReasons().empty());
}

TEST_F(BlockListTest, BlockUserAddsUserToList) {
    blocks->blockUser(*user1, "Спам");
    ASSERT_EQ(blocks->getBlockedUsers().size(), 1);
    EXPECT_EQ(blocks->getBlockedUsers()[0].getUsername(), "ivan");
    EXPECT_EQ(blocks->getBlockReasons()[0], "Спам");
}

TEST_F(BlockListTest, BlockUserThrowsIfDuplicate) {
    blocks->blockUser(*user1, "Нарушение правил");
    EXPECT_THROW(blocks->blockUser(*user1, "Повторное нарушение"), DuplicateUsernameException);
}

TEST_F(BlockListTest, UnblockUserRemovesUserFromList) {
    blocks->blockUser(*user1, "Флуд");
    ASSERT_EQ(blocks->getBlockedUsers().size(), 1);
    blocks->unblockUser(*user1);
    EXPECT_TRUE(blocks->getBlockedUsers().empty());
}

TEST_F(BlockListTest, UnblockUserDoesNothingIfNotFound) {
    blocks->blockUser(*user1, "Флуд");
    blocks->unblockUser(*user2);
    EXPECT_EQ(blocks->getBlockedUsers().size(), 1);
    EXPECT_EQ(blocks->getBlockedUsers()[0].getUsername(), "ivan");
}
