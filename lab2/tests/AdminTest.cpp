#include <gtest/gtest.h>
#include "Admin.h"
#include "UserProfile.h"
#include "Settings.h"
#include "Wallet.h"
#include "FriendList.h"
#include "BlockList.h"
#include "Currency.h"

class AdminTest : public ::testing::Test {
protected:
    UserProfile* profile;
    Settings* settings;
    Currency* currency;
    Wallet* wallet;
    FriendList* friends;
    BlockList* blocks;
    vector<Permission>* permissions;
    User* user;
    User* otherUser;
    Ban* ban;
    Admin* admin;

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

        user = new User(1, "admin", "admin@example.com", "adminpass", true,
            *profile, *settings, *wallet, *friends, *blocks, UserRole::ADMIN, *permissions);

        otherUser = new User(2,"user","user@example.com", "12345", false,
            *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);

        ban = new Ban("Спам", *otherUser);
        admin = new Admin("superuser", *permissions, vector<Ban>{}, * user);
    }

    void TearDown() override {
        delete admin; delete ban; delete otherUser; delete permissions; delete blocks; 
        delete friends;  delete wallet;  delete settings; delete currency; delete profile;
    }
};

TEST_F(AdminTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(admin->getAccessLevel(), "superuser");
    EXPECT_EQ(admin->getPermissions().size(), 2);
    EXPECT_EQ(admin->getUser().getUsername(), "admin");
}

TEST_F(AdminTest, SettersWorkCorrectly) {
    vector<Permission> newPerms{ Permission("EXECUTE", "Выполнение кода", true) };
    vector<Ban> newBans{ *ban };

    admin->setAccessLevel("moderator");
    admin->setPermissions(newPerms);
    admin->setBans(newBans);
    admin->setUser(*otherUser);

    EXPECT_EQ(admin->getAccessLevel(), "moderator");
    EXPECT_EQ(admin->getPermissions().size(), 1);
    EXPECT_EQ(admin->getPermissions()[0].getName(), "EXECUTE");
    EXPECT_EQ(admin->getBans().size(), 1);
    EXPECT_EQ(admin->getUser().getUsername(), "user");
}

TEST_F(AdminTest, BanUserAddsBanToList) {
    admin->banUser(*otherUser, "Нарушение правил");
    EXPECT_EQ(admin->getBans().size(), 1);
    EXPECT_EQ(admin->getBans()[0].getReason(), "Нарушение правил");
    EXPECT_EQ(admin->getBans()[0].getBannedUser().getId(), 2);
}

TEST_F(AdminTest, UnbanUserRemovesCorrectBan) {
    admin->banUser(*otherUser, "Флуд");
    EXPECT_EQ(admin->getBans().size(), 1);

    admin->unbanUser(2);
    EXPECT_EQ(admin->getBans().size(), 0);
}

TEST_F(AdminTest, UnbanUserDoesNotAffectOtherBans) {
    User* thirdUser = new User(3, "third", "third@example.com", "pass", false,
        *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);

    admin->banUser(*otherUser, "Флуд");
    admin->banUser(*thirdUser, "Оскорбления");

    EXPECT_EQ(admin->getBans().size(), 2);

    admin->unbanUser(2);
    EXPECT_EQ(admin->getBans().size(), 1);
    EXPECT_EQ(admin->getBans()[0].getBannedUser().getId(), 3);

    delete thirdUser;
}
