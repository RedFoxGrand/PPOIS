#include <gtest/gtest.h>
#include "FriendRequest.h"
#include "UserProfile.h"
#include "Settings.h"
#include "Wallet.h"
#include "FriendList.h"
#include "BlockList.h"
#include "Permission.h"
#include "Currency.h"

using namespace std;

class FriendRequestTest : public ::testing::Test {
protected:
    UserProfile* profile; Settings* settings; Currency* currency; Wallet* wallet;
    FriendList* friends; BlockList* blocks; vector<Permission>* permissions;
    User* sender; User* receiver; FriendRequest* request;

    void SetUp() override {
        profile = new UserProfile("Иван", "Иванов", "12.01.2007", "01.09.2023",
            "+375291234567", "Беларусь", "Минск", { "Игры", "Программирование" });
        settings = new Settings(18, "Русский", true, true, false, true, Theme::LIGHT);
        currency = new Currency("BYN", "Белорусский рубль", 1.0);
        wallet = new Wallet(5000.0, {}, {}, *currency);
        friends = new FriendList({}, {}, {});
        blocks = new BlockList({}, {});
        permissions = new vector<Permission>{ Permission("SEND_FRIEND_REQUEST", "Отправка запроса в друзья", true) };

        sender = new User(1, "sender", "sender@mail.ru", "12345", true,
            *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);
        receiver = new User(2, "receiver", "receiver@mail.ru", "54321", true,
            *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);

        request = new FriendRequest("01.01.2025 12:00:00", "", *sender, *receiver, FriendRequestStatus::PENDING);
    }

    void TearDown() override {
        delete request; delete receiver; delete sender; delete permissions;
        delete blocks; delete friends; delete wallet; delete settings;
        delete currency; delete profile;
    }
};

TEST_F(FriendRequestTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(request->getSentDate(), "01.01.2025 12:00:00");
    EXPECT_EQ(request->getResponseDate(), "");
    EXPECT_EQ(request->getSender().getUsername(), "sender");
    EXPECT_EQ(request->getReceiver().getUsername(), "receiver");
    EXPECT_EQ(request->getStatus(), FriendRequestStatus::PENDING);
}

TEST_F(FriendRequestTest, SettersChangeValuesCorrectly) {
    request->setSentDate("02.02.2025 14:00:00");
    request->setResponseDate("03.02.2025 10:00:00");
    request->setStatus(FriendRequestStatus::REJECTED);
    request->setSender(*receiver);
    request->setReceiver(*sender);

    EXPECT_EQ(request->getSentDate(), "02.02.2025 14:00:00");
    EXPECT_EQ(request->getResponseDate(), "03.02.2025 10:00:00");
    EXPECT_EQ(request->getStatus(), FriendRequestStatus::REJECTED);
    EXPECT_EQ(request->getSender().getUsername(), "receiver");
    EXPECT_EQ(request->getReceiver().getUsername(), "sender");
}

TEST_F(FriendRequestTest, AcceptChangesStatusAndSetsResponseDate) {
    request->accept();
    EXPECT_EQ(request->getStatus(), FriendRequestStatus::ACCEPTED);
    EXPECT_FALSE(request->getResponseDate().empty());
}

TEST_F(FriendRequestTest, SecondAcceptDoesNotChangeStatus) {
    request->accept();
    string firstResponseDate = request->getResponseDate();
    request->accept();
    EXPECT_EQ(request->getStatus(), FriendRequestStatus::ACCEPTED);
    EXPECT_EQ(request->getResponseDate(), firstResponseDate);
}

TEST_F(FriendRequestTest, RejectChangesStatusAndSetsResponseDate) {
    request->reject();
    EXPECT_EQ(request->getStatus(), FriendRequestStatus::REJECTED);
    EXPECT_FALSE(request->getResponseDate().empty());
}

TEST_F(FriendRequestTest, RejectDoesNothingIfNotPending) {
    request->reject();
    string firstResponseDate = request->getResponseDate();
    request->reject();
    EXPECT_EQ(request->getStatus(), FriendRequestStatus::REJECTED);
    EXPECT_EQ(request->getResponseDate(), firstResponseDate);
}
