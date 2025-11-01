#include <gtest/gtest.h>
#include "ConveyorBelt.h"

class ConveyorBeltTest : public ::testing::Test {
protected:
    ContactInfo* contact; Visa* visa; Passport* passport; Passenger* passenger;
    BaggageTag* tag1; BaggageTag* tag2; Baggage* baggage1; Baggage* baggage2;
    vector<Baggage> baggageList; ConveyorBelt* belt; time_t birthDate; time_t issueDate; time_t expiryDate;

    void SetUp() override {
        birthDate = time(nullptr) - 86400 * 10000;
        issueDate = time(nullptr) - 86400 * 100;  
        expiryDate = time(nullptr) + 86400 * 365; 

        contact = new ContactInfo("test@mail.com", "+79001234567", "Москва, Россия");
        visa = new Visa("V123", "Франция", issueDate, expiryDate, VisaType::Tourist);
        passport = new Passport("PP123456", "Россия", "Сергей Иванов", issueDate, expiryDate, *visa, MaritalStatus::NotMarried);
        passenger = new Passenger("Сергей", "Иванов", birthDate, *contact, "P001", *passport);

        tag1 = new BaggageTag("T001", "B001", "SU101", "Париж");
        tag2 = new BaggageTag("T002", "B002", "SU202", "Сочи");

        std::vector<std::string> items1 = { "куртка", "обувь" };
        std::vector<std::string> items2 = { "футболка", "брюки" };

        baggage1 = new Baggage("B001", 15.5, *passenger, *tag1, BaggageStatus::CheckedIn, items1);
        baggage2 = new Baggage("B002", 22.3, *passenger, *tag2, BaggageStatus::CheckedIn, items2);

        baggageList = { *baggage1, *baggage2 };
        belt = new ConveyorBelt("Зона A", true, baggageList, 2.5, 3);
    }

    void TearDown() override {
        delete contact; delete visa; delete passport; delete passenger;
        delete tag1; delete tag2; delete baggage1; delete baggage2; delete belt;
    }
};

TEST_F(ConveyorBeltTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(belt->getLocation(), "Зона A");
    EXPECT_TRUE(belt->getIsActive());
    EXPECT_DOUBLE_EQ(belt->getSpeed(), 2.5);
    EXPECT_EQ(belt->getCapacity(), 3);
    EXPECT_EQ(belt->getCurrentBaggage().size(), 2);
}

TEST_F(ConveyorBeltTest, SettersWorkCorrectly) {
    belt->setLocation("Зона B");
    belt->setActive(false);
    belt->setSpeed(3.2);
    belt->setCapacity(5);

    std::vector<Baggage> newList = { *baggage1 };
    belt->setCurrentBaggage(newList);

    EXPECT_EQ(belt->getLocation(), "Зона B");
    EXPECT_FALSE(belt->getIsActive());
    EXPECT_DOUBLE_EQ(belt->getSpeed(), 3.2);
    EXPECT_EQ(belt->getCapacity(), 5);
    EXPECT_EQ(belt->getCurrentBaggage().size(), 1);
}

TEST_F(ConveyorBeltTest, StartAndStopWorkCorrectly) {
    belt->stop();
    EXPECT_FALSE(belt->getIsActive());

    belt->start();
    EXPECT_TRUE(belt->getIsActive());
}

TEST_F(ConveyorBeltTest, UnloadBaggageRemovesItemById) {
    belt->unloadBaggage("B001");
    EXPECT_EQ(belt->getCurrentBaggage().size(), 1);
    EXPECT_EQ(belt->getCurrentBaggage()[0].getBaggageId(), "B002");
}

TEST_F(ConveyorBeltTest, UnloadBaggageDoesNothingIfNotFound) {
    belt->unloadBaggage("B999");
    EXPECT_EQ(belt->getCurrentBaggage().size(), 2);
}

TEST_F(ConveyorBeltTest, AdjustSpeedWorksCorrectly) {
    belt->adjustSpeed(4.5);
    EXPECT_DOUBLE_EQ(belt->getSpeed(), 4.5);

    belt->adjustSpeed(-2.0);
    EXPECT_DOUBLE_EQ(belt->getSpeed(), 4.5);
}

TEST_F(ConveyorBeltTest, IsOverloadedDetectsCorrectly) {
    EXPECT_FALSE(belt->isOverloaded());

    belt->setCapacity(2);
    EXPECT_TRUE(belt->isOverloaded());
}
