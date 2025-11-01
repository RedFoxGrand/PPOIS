#include <gtest/gtest.h>
#include "Cargo.h"

static Passenger createTestPassenger() {
    time_t now = time(nullptr);
    Visa visa("V123", "USA", now, now + 60 * 60 * 24 * 365, VisaType::Tourist);
    Passport passport("P12345", "USA", "John Doe", now, now + 60 * 60 * 24 * 365, visa, MaritalStatus::NotMarried);
    ContactInfo info = { "john@example.com", "+123456789", "123 Street, NY" };
    Passenger passenger("John", "Doe", now - 60 * 60 * 24 * 365 * 30, info, "PID001", passport);
    return passenger;
}

TEST(CargoTest, ConstructorInitializesAllFields) {
    Passenger passenger = createTestPassenger();

    Cargo cargo(150.5, "Electronics", passenger);

    EXPECT_DOUBLE_EQ(cargo.getWeight(), 150.5);
    EXPECT_EQ(cargo.getDescription(), "Electronics");
    EXPECT_EQ(cargo.getOwner().getPassengerId(), "PID001");
    EXPECT_EQ(cargo.getOwner().getFullName(), "John Doe");
}

TEST(CargoTest, SettersModifyFieldsCorrectly) {
    Passenger passenger = createTestPassenger();
    Cargo cargo(50.0, "Books", passenger);

    Passenger newPassenger = createTestPassenger();
    newPassenger.setPassengerId("PID777");

    cargo.setWeight(200.0);
    cargo.setDescription("Machinery");
    cargo.setOwner(newPassenger);

    EXPECT_DOUBLE_EQ(cargo.getWeight(), 200.0);
    EXPECT_EQ(cargo.getDescription(), "Machinery");
    EXPECT_EQ(cargo.getOwner().getPassengerId(), "PID777");
}

TEST(CargoTest, GettersReturnCorrectValues) {
    Passenger passenger = createTestPassenger();
    Cargo cargo(10.0, "Documents", passenger);

    EXPECT_DOUBLE_EQ(cargo.getWeight(), 10.0);
    EXPECT_EQ(cargo.getDescription(), "Documents");
    EXPECT_EQ(cargo.getOwner().getFullName(), "John Doe");
}

TEST(CargoTest, CanChangeOwner) {
    Passenger original = createTestPassenger();
    Cargo cargo(70.0, "Equipment", original);

    Passenger newOwner = createTestPassenger();
    newOwner.setPassengerId("PID999");

    cargo.setOwner(newOwner);
    EXPECT_EQ(cargo.getOwner().getPassengerId(), "PID999");
}
