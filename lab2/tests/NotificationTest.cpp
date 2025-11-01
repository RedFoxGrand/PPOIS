#include <gtest/gtest.h>
#include "Notification.h"
#include "UserProfile.h"
#include "Settings.h"
#include "Wallet.h"
#include "FriendList.h"
#include "BlockList.h"
#include "Permission.h"
#include "Currency.h"

using namespace std;

class NotificationTest : public ::testing::Test {
protected:
    UserProfile* profile; Settings* settings; Currency* currency; Wallet* wallet;
    FriendList* friends; BlockList* blocks; vector<Permission>* permissions;
    User* recipient; Notification* notification;

    void SetUp() override {
        profile = new UserProfile("Иван", "Иванов", "12.01.2007", "01.09.2023",
            "+375291234567", "Беларусь", "Минск", { "Игры", "Программирование" });
        settings = new Settings(18, "Русский", true, true, false, true, Theme::LIGHT);
        currency = new Currency("BYN", "Белорусский рубль", 1.0);
        wallet = new Wallet(1000.0, {}, {}, *currency);
        friends = new FriendList({}, {}, {});
        blocks = new BlockList({}, {});
        permissions = new vector<Permission>{ Permission("VIEW_NOTIFICATIONS", "Просмотр уведомлений", true) };

        recipient = new User(1, "ivan123", "ivan@example.com", "1234", true,
            *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);

        notification = new Notification("Новое сообщение", "24.10.2025 12:00:00", false, *recipient);
    }

    void TearDown() override {
        delete notification; delete recipient; delete permissions; delete blocks;
        delete friends; delete wallet; delete currency; delete settings; delete profile;
    }
};

TEST_F(NotificationTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(notification->getMessage(), "Новое сообщение");
    EXPECT_EQ(notification->getCreatedDate(), "24.10.2025 12:00:00");
    EXPECT_FALSE(notification->getIsRead());
    EXPECT_EQ(notification->getRecipient().getUsername(), "ivan123");
}

TEST_F(NotificationTest, SetAndGetMessageWorkCorrectly) {
    notification->setMessage("Вам пришло приглашение");
    EXPECT_EQ(notification->getMessage(), "Вам пришло приглашение");
}

TEST_F(NotificationTest, SetAndGetCreatedDateWorkCorrectly) {
    notification->setCreatedDate("25.10.2025 09:30:00");
    EXPECT_EQ(notification->getCreatedDate(), "25.10.2025 09:30:00");
}

TEST_F(NotificationTest, SetAndGetIsReadWorkCorrectly) {
    notification->setIsRead(true);
    EXPECT_TRUE(notification->getIsRead());
    notification->setIsRead(false);
    EXPECT_FALSE(notification->getIsRead());
}

TEST_F(NotificationTest, SetAndGetRecipientWorkCorrectly) {
    UserProfile profile2("Анна", "Смирнова", "02.02.1998", "01.01.2020",
        "+375447778899", "Беларусь", "Гродно", { "Музыка" });
    Settings settings2(25, "Русский", true, false, false, true, Theme::DARK);
    Currency currency2("USD", "Доллар США", 3.2);
    Wallet wallet2(200.0, {}, {}, currency2);
    FriendList friends2({}, {}, {});
    BlockList blocks2({}, {});
    vector<Permission> permissions2{ Permission("SEND_MESSAGES", "Отправка сообщений", true) };
    User anna(2, "anna98", "anna@example.com", "pass", true,
        profile2, settings2, wallet2, friends2, blocks2, UserRole::USER, permissions2);

    notification->setRecipient(anna);
    EXPECT_EQ(notification->getRecipient().getUsername(), "anna98");
    EXPECT_EQ(notification->getRecipient().getEmail(), "anna@example.com");
}

TEST_F(NotificationTest, MarkAsReadSetsIsReadTrue) {
    EXPECT_FALSE(notification->getIsRead());
    notification->markAsRead();
    EXPECT_TRUE(notification->getIsRead());
}

TEST_F(NotificationTest, MarkAsReadIsIdempotent) {
    notification->setIsRead(true);
    notification->markAsRead();
    EXPECT_TRUE(notification->getIsRead());
}

TEST_F(NotificationTest, AllSettersWorkTogether) {
    notification->setMessage("Уведомление обновлено");
    notification->setCreatedDate("25.10.2025 10:10:10");
    notification->setIsRead(true);

    EXPECT_EQ(notification->getMessage(), "Уведомление обновлено");
    EXPECT_EQ(notification->getCreatedDate(), "25.10.2025 10:10:10");
    EXPECT_TRUE(notification->getIsRead());
}
