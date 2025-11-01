#include <gtest/gtest.h>
#include "CateringOrder.h"

class CateringOrderTest : public ::testing::Test {
protected:
    ContactInfo* contact; Visa* visa; Passport* passport; Passenger* passenger;
    CateringOrder* order; time_t birthDate; time_t issueDate; time_t expiryDate; time_t orderTime;

    void SetUp() override {
        birthDate = time(nullptr) - 86400 * 365 * 25;
        issueDate = time(nullptr) - 86400 * 100;
        expiryDate = time(nullptr) + 86400 * 365;
        orderTime = time(nullptr);

        contact = new ContactInfo("mail@test.com", "+79001234567", "Saint-Petersburg, Russia");
        visa = new Visa("VISA01", "Italy", issueDate, expiryDate, VisaType::Tourist);
        passport = new Passport("P112233", "Russia", "Anna Ivanova", issueDate, expiryDate, *visa, MaritalStatus::NotMarried);
        passenger = new Passenger("Anna", "Ivanova", birthDate, *contact, "PSG100", *passport);

        vector<string> items = { "Tea", "Sandwich" };
        order = new CateringOrder(*passenger, items, 10.0, false, orderTime);
    }

    void TearDown() override {
        delete contact; delete visa; delete passport; delete passenger;  delete order;
    }
};

TEST_F(CateringOrderTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(order->getPassenger().getPassengerId(), "PSG100");
    EXPECT_EQ(order->getItems().size(), 2);
    EXPECT_EQ(order->getItems()[0], "Tea");
    EXPECT_DOUBLE_EQ(order->getTotalCost(), 10.0);
    EXPECT_FALSE(order->getIsDelivered());
    EXPECT_EQ(order->getOrderTime(), orderTime);
}

TEST_F(CateringOrderTest, SettersWorkCorrectly) {
    vector<string> newItems = { "Juice", "Cookie" };
    Passenger newPassenger("Elena", "Sidorova", birthDate, *contact, "PSG200", *passport);

    order->setPassenger(newPassenger);
    order->setItems(newItems);
    order->setTotalCost(25.0);
    order->setDelivered(true);
    order->setOrderTime(issueDate);

    EXPECT_EQ(order->getPassenger().getPassengerId(), "PSG200");
    EXPECT_EQ(order->getItems().size(), 2);
    EXPECT_EQ(order->getItems()[0], "Juice");
    EXPECT_DOUBLE_EQ(order->getTotalCost(), 25.0);
    EXPECT_TRUE(order->getIsDelivered());
    EXPECT_EQ(order->getOrderTime(), issueDate);
}

TEST_F(CateringOrderTest, AddItemAddsNewItemToList) {
    order->addItem("Coffee");
    EXPECT_EQ(order->getItems().size(), 3);
    EXPECT_EQ(order->getItems().back(), "Coffee");
}

TEST_F(CateringOrderTest, CalculateTotalPriceCalculatesCorrectly) {
    order->calculateTotalPrice(5.0);

    EXPECT_DOUBLE_EQ(order->getTotalCost(), 20.0);
}

TEST_F(CateringOrderTest, CalculateTotalPriceThrowsIfNegativePrice) {
    EXPECT_THROW(order->calculateTotalPrice(-3.0), InvalidBalanceException);
}
