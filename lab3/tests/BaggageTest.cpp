#include <gtest/gtest.h>
#include "Baggage.h"

class BaggageFixture : public ::testing::Test {
protected:
    Passenger* passenger;
    BaggageTag* tag;
    Baggage* baggage;

    void SetUp() override {
        time_t now = time(nullptr);
        time_t expiry = now + 31536000;

        ContactInfo contact("john@example.com", "+123456789", "New York");
        Visa visa("VISA123", "USA", now, expiry, VisaType::Tourist);
        Passport passport("P12345", "USA", "John Doe", now, expiry, visa, MaritalStatus::NotMarried);
        *(&passport);

        passenger = new Passenger("John", "Doe", now - (30 * 365 * 24 * 3600),
            contact, "PSG001", passport);

        tag = new BaggageTag("TAG001", "BG001", "FL123", "London");

        baggage = new Baggage("BG001", 23.5, *passenger, *tag,
            BaggageStatus::NotCheckedIn, { "Shoes", "Clothes" });
    }

    void TearDown() override {
        delete passenger; delete tag; delete baggage;
    }
};

// --- Проверка конструктора ---
TEST_F(BaggageFixture, ConstructorInitializesCorrectly) {
    EXPECT_EQ(baggage->getBaggageId(), "BG001");
    EXPECT_DOUBLE_EQ(baggage->getWeight(), 23.5);
    EXPECT_EQ(baggage->getTag().getFlightNumber(), "FL123");
    EXPECT_EQ(baggage->getStatus(), BaggageStatus::NotCheckedIn);
    EXPECT_EQ(baggage->getItems().size(), 2);
    EXPECT_EQ(baggage->getItems()[0], "Shoes");
}

// --- Проверка сеттеров и геттеров ---
TEST_F(BaggageFixture, SettersAndGettersWorkCorrectly) {
    baggage->setBaggageId("BG999");
    baggage->setWeight(18.7);
    baggage->setStatus(BaggageStatus::Delivered);

    EXPECT_EQ(baggage->getBaggageId(), "BG999");
    EXPECT_DOUBLE_EQ(baggage->getWeight(), 18.7);
    EXPECT_EQ(baggage->getStatus(), BaggageStatus::Delivered);

    vector<string> newItems = { "Laptop", "Camera" };
    baggage->setItems(newItems);
    EXPECT_EQ(baggage->getItems().size(), 2);
    EXPECT_EQ(baggage->getItems()[1], "Camera");
}

// --- Проверка assignTag() ---
TEST_F(BaggageFixture, AssignTagSetsNewTagAndStatusCheckedIn) {
    BaggageTag newTag("TAG999", "BG001", "FL777", "Berlin");
    baggage->assignTag(newTag);

    EXPECT_EQ(baggage->getTag().getTagCode(), "TAG999");
    EXPECT_EQ(baggage->getStatus(), BaggageStatus::CheckedIn);
}

// --- Проверка addItem() ---
TEST_F(BaggageFixture, AddItemAddsNewElement) {
    size_t oldSize = baggage->getItems().size();
    baggage->addItem("Book");

    EXPECT_EQ(baggage->getItems().size(), oldSize + 1);
    EXPECT_EQ(baggage->getItems().back(), "Book");
}

// --- Проверка postItem() ---
TEST_F(BaggageFixture, PostItemRemovesExistingElement) {
    baggage->addItem("Watch");
    baggage->postItem("Watch");

    auto& items = baggage->getItems();
    EXPECT_EQ(find(items.begin(), items.end(), "Watch"), items.end());
}

// --- Проверка markLost() ---
TEST_F(BaggageFixture, MarkLostChangesStatusToLost) {
    baggage->markLost();
    EXPECT_EQ(baggage->getStatus(), BaggageStatus::Lost);
}
