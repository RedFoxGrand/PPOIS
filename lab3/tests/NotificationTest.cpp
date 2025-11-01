#include "gtest/gtest.h"
#include "Notification.h"

class NotificationTest : public ::testing::Test {
protected:
    ContactInfo* contact; Visa* visa; Passport* passport;
    Passenger* passenger; Notification* notification; time_t now;

    void SetUp() override {
        now = time(nullptr);

        contact = new ContactInfo("ivanov@example.com", "+79991234567", "Россия, Москва");
        visa = new Visa("V123", "Германия", now - 200000, now + 500000, VisaType::Tourist);
        passport = new Passport("PP123456", "Россия", "Иван Иванов", now - 600000, now + 800000, *visa, MaritalStatus::Married);
        passenger = new Passenger("Иван", "Иванов", now - 1000000000, *contact, "P001", *passport);

        notification = new Notification(*passenger, "Ваш рейс успешно зарегистрирован", now, false);
    }

    void TearDown() override {
        delete contact; delete visa; delete passport; delete passenger; delete notification;
    }
};

TEST_F(NotificationTest, ConstructorInitializesAllFieldsCorrectly) {
    EXPECT_EQ(notification->getRecipient().getPassengerId(), "P001");
    EXPECT_EQ(notification->getMessage(), "Ваш рейс успешно зарегистрирован");
    EXPECT_EQ(notification->getTimestamp(), now);
    EXPECT_FALSE(notification->getIsRead());
}

TEST_F(NotificationTest, SettersChangeValuesCorrectly) {
    ContactInfo contact2("petrov@example.com", "+79995554433", "Россия, Санкт-Петербург");
    Visa visa2("V777", "Франция", now - 400000, now + 600000, VisaType::Business);
    Passport passport2("PP654321", "Россия", "Андрей Петров", now - 700000, now + 900000, visa2, MaritalStatus::NotMarried);
    Passenger passenger2("Андрей", "Петров", now - 1200000000, contact2, "P002", passport2);

    time_t later = now + 1000;

    notification->setRecipient(passenger2);
    notification->setMessage("Изменение времени вылета");
    notification->setTimestamp(later);
    notification->setIsRead(true);

    EXPECT_EQ(notification->getRecipient().getPassengerId(), "P002");
    EXPECT_EQ(notification->getRecipient().getFullName(), "Андрей Петров");
    EXPECT_EQ(notification->getMessage(), "Изменение времени вылета");
    EXPECT_EQ(notification->getTimestamp(), later);
    EXPECT_TRUE(notification->getIsRead());
}

TEST_F(NotificationTest, GetRecipientReturnsCorrectPassenger) {
    const Passenger& recipient = notification->getRecipient();
    EXPECT_EQ(recipient.getFullName(), "Иван Иванов");
    EXPECT_EQ(recipient.getContactInfo().getEmail(), "ivanov@example.com");
}

TEST_F(NotificationTest, MarkAsReadChangesStatusToTrue) {
    EXPECT_FALSE(notification->getIsRead());
    notification->markAsRead();
    EXPECT_TRUE(notification->getIsRead());
}

TEST_F(NotificationTest, MultipleChangesUpdateFieldsCorrectly) {
    notification->setMessage("Ваш рейс перенесён на 18:30");
    notification->markAsRead();

    EXPECT_EQ(notification->getMessage(), "Ваш рейс перенесён на 18:30");
    EXPECT_TRUE(notification->getIsRead());
}
