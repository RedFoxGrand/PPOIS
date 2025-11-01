#include <gtest/gtest.h>
#include "User.h"
#include "Permission.h"
#include "Settings.h"
#include "Wallet.h"
#include "FriendList.h"
#include "BlockList.h"
#include "UserProfile.h"
#include "Currency.h"

class UserTest : public ::testing::Test {
protected:
    UserProfile* profile; Settings* settings; Currency* currency; Wallet* wallet;
    FriendList* friends; BlockList* blocks; vector<Permission>* permissions; User* user;

    void SetUp() override {
        profile = new UserProfile("Иван", "Иванов", "12.01.2007", "01.09.2023",
            "+375291234567", "Беларусь", "Минск", { "Игры", "Программирование" });
        settings = new Settings(18, "Русский", true, true, false, true, Theme::LIGHT);
        currency = new Currency("BYN", "Белорусский рубль", 1.0);
        wallet = new Wallet(1000.0, {}, {}, *currency);
        friends = new FriendList({}, {}, {});
        blocks = new BlockList({}, {});
        permissions = new vector<Permission>{
            Permission("READ", "Чтение данных", true),
            Permission("WRITE", "Запись данных", true)
        };
        user = new User(1, "ivan", "ivan@mail.ru", "1234", false,
            *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);
    }

    void TearDown() override {
        delete user; delete permissions; delete blocks; delete friends;
        delete wallet; delete settings; delete currency; delete profile;
    }
};

TEST_F(UserTest, ConstructorAndGetters) {
    EXPECT_EQ(user->getId(), 1);
    EXPECT_EQ(user->getUsername(), "ivan");
    EXPECT_EQ(user->getEmail(), "ivan@mail.ru");
    EXPECT_FALSE(user->isVerifiedUser());
    EXPECT_EQ(user->getPermissions().size(), 2);
}

TEST_F(UserTest, VerifyAccountWorks) {
    EXPECT_FALSE(user->isVerifiedUser());
    user->verifyAccount();
    EXPECT_TRUE(user->isVerifiedUser());
}

TEST_F(UserTest, AddPermissionIncreasesCount) {
    Permission* admin = new Permission("ADMIN", "Права администратора", true);
    size_t before = user->getPermissions().size();
    user->addPermission(*admin);
    EXPECT_EQ(user->getPermissions().size(), before + 1);
    EXPECT_EQ(user->getPermissions().back().getName(), "ADMIN");
    delete admin;
}

TEST_F(UserTest, RemovePermissionWorks) {
    Permission* permToRemove = new Permission("READ", "Чтение данных", true);
    size_t before = user->getPermissions().size();
    user->removePermission(*permToRemove);
    EXPECT_EQ(user->getPermissions().size(), before - 1);
    delete permToRemove;
}

TEST_F(UserTest, RemoveNonexistentPermissionDoesNotChangeCount) {
    Permission* fake = new Permission("FAKE", "Несуществующее", true);
    size_t before = user->getPermissions().size();
    user->removePermission(*fake);
    EXPECT_EQ(user->getPermissions().size(), before);
    delete fake;
}

TEST_F(UserTest, LoginThrowsIfNotVerified) {
    EXPECT_THROW(user->login("1234"), InvalidPasswordException);
}

TEST_F(UserTest, LoginThrowsIfWrongPassword) {
    user->verifyAccount();
    EXPECT_THROW(user->login("wrong_pass"), InvalidPasswordException);
}

TEST_F(UserTest, LoginSuccessWhenVerifiedAndPasswordCorrect) {
    user->verifyAccount();
    EXPECT_NO_THROW(user->login("1234"));
}

TEST_F(UserTest, SettersUpdateValues) {
    user->setUsername("new_name");
    user->setEmail("new@mail.ru");
    user->setVerified(true);
    EXPECT_EQ(user->getUsername(), "new_name");
    EXPECT_EQ(user->getEmail(), "new@mail.ru");
    EXPECT_TRUE(user->isVerifiedUser());
}
