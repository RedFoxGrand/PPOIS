#include <gtest/gtest.h>
#include "Invoice.h"
#include "User.h"
#include "UserProfile.h"
#include "Settings.h"
#include "Wallet.h"
#include "FriendList.h"
#include "BlockList.h"
#include "Permission.h"
#include "Currency.h"

class InvoiceTest : public ::testing::Test {
protected:
    UserProfile* profile; Settings* settings; Currency* currency; Wallet* wallet;
    FriendList* friends; BlockList* blocks; vector<Permission>* permissions;
    User* user; Invoice* invoice;

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
        user = new User(1, "alice", "alice@example.com", "12345", true,
            *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);
        invoice = new Invoice(500.0, "2025-12-31", *user, InvoiceStatus::PENDING);
    }

    void TearDown() override {
        delete invoice; delete user; delete permissions; delete blocks;
        delete friends; delete wallet; delete settings; delete currency; delete profile;
    }
};

TEST_F(InvoiceTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(invoice->getAmount(), 500.0);
    EXPECT_EQ(invoice->getDueDate(), "2025-12-31");
    EXPECT_EQ(invoice->getStatus(), InvoiceStatus::PENDING);
    EXPECT_EQ(invoice->getPayer().getUsername(), "alice");
}

TEST_F(InvoiceTest, SettersWorkCorrectly) {
    FriendList* localFriends = new FriendList({}, {}, {});
    BlockList* localBlocks = new BlockList({}, {});
    User* bob = new User(2, "bob", "bob@example.com", "qwerty", false,
        *profile, *settings, *wallet, *localFriends, *localBlocks,
        UserRole::USER, *permissions);

    invoice->setAmount(999.99);
    invoice->setDueDate("2026-01-01");
    invoice->setStatus(InvoiceStatus::OVERDUE);
    invoice->setPayer(*bob);

    EXPECT_EQ(invoice->getAmount(), 999.99);
    EXPECT_EQ(invoice->getDueDate(), "2026-01-01");
    EXPECT_EQ(invoice->getStatus(), InvoiceStatus::OVERDUE);
    EXPECT_EQ(invoice->getPayer().getUsername(), "bob");

    delete bob; delete localFriends; delete localBlocks;
}

TEST_F(InvoiceTest, MarkAsPaidChangesStatusToPaid) {
    invoice->markAsPaid();
    EXPECT_EQ(invoice->getStatus(), InvoiceStatus::PAID);
}

TEST_F(InvoiceTest, IsOverdueReturnsTrueForOverdue) {
    invoice->setStatus(InvoiceStatus::OVERDUE);
    EXPECT_TRUE(invoice->isOverdue());
}

TEST_F(InvoiceTest, IsOverdueReturnsFalseWhenNotOverdue) {
    invoice->setStatus(InvoiceStatus::PENDING);
    EXPECT_FALSE(invoice->isOverdue());
}

TEST_F(InvoiceTest, CanChangePayerAfterCreation) {
    FriendList* tempFriends = new FriendList({}, {}, {});
    BlockList* tempBlocks = new BlockList({}, {});
    User* charlie = new User(3, "charlie", "charlie@example.com", "zxcvb", true,
        *profile, *settings, *wallet, *tempFriends, *tempBlocks,
        UserRole::USER, *permissions);

    invoice->setPayer(*charlie);
    EXPECT_EQ(invoice->getPayer().getUsername(), "charlie");

    delete charlie; delete tempFriends; delete tempBlocks;
}
