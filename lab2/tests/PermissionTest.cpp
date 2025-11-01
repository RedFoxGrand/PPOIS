#include <gtest/gtest.h>
#include "Permission.h"
#include "User.h"
#include "UserProfile.h"
#include "Settings.h"
#include "Wallet.h"
#include "FriendList.h"
#include "BlockList.h"
#include "Currency.h"

class PermissionTest : public ::testing::Test {
protected:
    UserProfile* profile; Settings* settings; Currency* currency; Wallet* wallet;
    FriendList* friends; BlockList* blocks; vector<Permission>* permissions;
    User* user; Permission* readPermission; Permission* writePermission;

    void SetUp() override {
        profile = new UserProfile("Иван", "Иванов", "12.01.2007", "01.09.2023",
            "+375291234567", "Беларусь", "Минск", { "Игры", "Программирование" });
        settings = new Settings(18, "Русский", true, true, false, true, Theme::LIGHT);
        currency = new Currency("BYN", "Белорусский рубль", 1.0);
        wallet = new Wallet(5000.0, {}, {}, *currency);
        friends = new FriendList({}, {}, {});
        blocks = new BlockList({}, {});
        permissions = new vector<Permission>{ Permission("READ", "Чтение данных", true) };

        user = new User(1, "alice", "alice@example.com", "12345", true,
            *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);

        readPermission = new Permission("READ", "Чтение данных", true);
        writePermission = new Permission("WRITE", "Изменение данных", false);
    }

    void TearDown() override {
        delete writePermission; delete readPermission; delete user; delete permissions;
        delete blocks; delete friends; delete wallet; delete settings; delete currency; delete profile;
    }
};

TEST_F(PermissionTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(readPermission->getName(), "READ");
    EXPECT_EQ(readPermission->getDescription(), "Чтение данных");
    EXPECT_TRUE(readPermission->getRevocable());
}

TEST_F(PermissionTest, SettersUpdateValuesCorrectly) {
    readPermission->setName("EXECUTE");
    readPermission->setDescription("Выполнение программ");
    readPermission->setRevocable(false);

    EXPECT_EQ(readPermission->getName(), "EXECUTE");
    EXPECT_EQ(readPermission->getDescription(), "Выполнение программ");
    EXPECT_FALSE(readPermission->getRevocable());
}

TEST_F(PermissionTest, GrantToAddsPermissionToUser) {
    Permission newPermission("SHARE", "Делиться контентом", true);
    user->addPermission(newPermission);

    bool found = false;
    for (const auto& p : user->getPermissions()) {
        if (p.getName() == "SHARE") { found = true; break; }
    }
    EXPECT_TRUE(found);
}

TEST_F(PermissionTest, RevokeFromRemovesPermissionIfRevocable) {
    user->addPermission(*readPermission);
    size_t before = user->getPermissions().size();
    readPermission->revokeFrom(*user);
    size_t after = user->getPermissions().size();
    EXPECT_LT(after, before);
}

TEST_F(PermissionTest, RevokeFromDoesNotRemovePermissionIfNotRevocable) {
    user->addPermission(*writePermission);
    size_t before = user->getPermissions().size();
    writePermission->revokeFrom(*user);
    size_t after = user->getPermissions().size();
    EXPECT_EQ(before, after);
}
