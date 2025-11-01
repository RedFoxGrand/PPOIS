#include <gtest/gtest.h>
#include "FriendList.h"
#include "User.h"
#include "UserProfile.h"
#include "Settings.h"
#include "Wallet.h"
#include "BlockList.h"
#include "Permission.h"
#include "Currency.h"

class FriendListTest : public ::testing::Test {
protected:
    UserProfile* profile; Settings* settings; Currency* currency; Wallet* wallet; FriendList* friends; BlockList* blocks; vector<Permission>* permissions; User* user1; User* user2; User* user3;

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

        user1 = new User(1, "ivan", "ivan@mail.ru", "1234", true,
            *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);
        user2 = new User(2, "petr", "petr@mail.ru", "5678", true,
            *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);
        user3 = new User(3, "olga", "olga@mail.ru", "pass", false,
            *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);
    }

    void TearDown() override {
        delete user1; delete user2; delete user3; delete permissions; delete blocks;
        delete friends; delete wallet; delete settings; delete currency; delete profile;
    }
};

TEST_F(FriendListTest, ConstructorInitializesEmptyLists) {
    EXPECT_TRUE(friends->getFriends().empty());
    EXPECT_TRUE(friends->getPendingRequests().empty());
    EXPECT_TRUE(friends->getSuggestedFriends().empty());
}

TEST_F(FriendListTest, AddFriendAddsUser) {
    friends->addFriend(*user1);
    ASSERT_EQ(friends->getFriends().size(), 1);
    EXPECT_EQ(friends->getFriends()[0].getUsername(), "ivan");
}

TEST_F(FriendListTest, AddFriendThrowsWhenDuplicate) {
    friends->addFriend(*user1);
    EXPECT_THROW(friends->addFriend(*user1), DuplicateUsernameException);
}

TEST_F(FriendListTest, RemoveFriendRemovesExistingUser) {
    friends->addFriend(*user1);
    friends->addFriend(*user2);
    friends->removeFriend(*user1);
    ASSERT_EQ(friends->getFriends().size(), 1);
    EXPECT_EQ(friends->getFriends()[0].getUsername(), "petr");
}

TEST_F(FriendListTest, RemoveFriendDoesNothingIfNotFound) {
    friends->addFriend(*user1);
    friends->removeFriend(*user2);
    EXPECT_EQ(friends->getFriends().size(), 1);
    EXPECT_EQ(friends->getFriends()[0].getUsername(), "ivan");
}

TEST_F(FriendListTest, SendFriendRequestAddsPendingUser) {
    friends->sendFriendRequest(*user3);
    ASSERT_EQ(friends->getPendingRequests().size(), 1);
    EXPECT_EQ(friends->getPendingRequests()[0].getUsername(), "olga");
}

TEST_F(FriendListTest, SendFriendRequestThrowsWhenDuplicate) {
    friends->sendFriendRequest(*user2);
    EXPECT_THROW(friends->sendFriendRequest(*user2), DuplicateUsernameException);
}
