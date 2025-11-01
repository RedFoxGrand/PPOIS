#include <gtest/gtest.h>
#include "PassengerManager.h"

class PassengerManagerTest : public ::testing::Test {
protected:
    ContactInfo* contact; Visa* visa; Passport* passport;
    Passenger* passenger; PassengerManager* manager;
    time_t birthDate; time_t issueDate; time_t expiryDate;

    void SetUp() override {
        birthDate = time(nullptr) - 86400 * 365 * 25;
        issueDate = time(nullptr) - 86400 * 100;
        expiryDate = time(nullptr) + 86400 * 365;

        contact = new ContactInfo("test@mail.com", "+79001234567", "Moscow, Russia");
        visa = new Visa("VISA123", "France", issueDate, expiryDate, VisaType::Tourist);
        passport = new Passport("P111222", "Russia", "Ivan Petrov", issueDate, expiryDate, *visa, MaritalStatus::NotMarried);

        passenger = new Passenger("Ivan", "Petrov", birthDate, *contact, "PID001", *passport);
        passenger->addTicket("TK001");

        std::vector<Passenger> passengers = { *passenger };
        manager = new PassengerManager(passengers);
    }

    void TearDown() override {
        delete contact; delete visa;  delete passport; delete passenger; delete manager;
    }
};

TEST_F(PassengerManagerTest, ConstructorInitializesPassengersCorrectly) {
    const auto& list = manager->getPassengers();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0].getPassengerId(), "PID001");
    EXPECT_EQ(list[0].getFullName(), "Ivan Petrov");
}

TEST_F(PassengerManagerTest, SetPassengersWorksCorrectly) {
    Passport newPassport("P333444", "Germany", "Anna Ivanova", issueDate, expiryDate, *visa, MaritalStatus::NotMarried);
    Passenger newPassenger("Anna", "Ivanova", birthDate, *contact, "PID002", newPassport);

    std::vector<Passenger> newList = { newPassenger };
    manager->setPassengers(newList);

    EXPECT_EQ(manager->getPassengers().size(), 1);
    EXPECT_EQ(manager->getPassengers()[0].getName(), "Anna");
}

TEST_F(PassengerManagerTest, RegisterPassengerAddsNewPassenger) {
    Person newPerson("Petr", "Sidorov", birthDate, *contact);
    manager->registerPassenger(newPerson);

    const auto& list = manager->getPassengers();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[1].getFullName(), "Petr Sidorov");
}

TEST_F(PassengerManagerTest, FindByPassportReturnsCorrectPassenger) {
    Passenger found = manager->findByPassport(*passport);
    EXPECT_EQ(found.getFullName(), "Ivan Petrov");
    EXPECT_EQ(found.getPassengerId(), "PID001");
}

TEST_F(PassengerManagerTest, FindByPassportThrowsIfNotFound) {
    Visa fakeVisa("V999", "UK", issueDate, expiryDate, VisaType::Tourist);
    Passport fakePassport("P999999", "UK", "Fake Person", issueDate, expiryDate, fakeVisa, MaritalStatus::Married);

    EXPECT_THROW(manager->findByPassport(fakePassport), PassengerNotFound);
}

TEST_F(PassengerManagerTest, GetPassengerHistoryReturnsCorrectPassenger) {
    Passenger hist = manager->getPassengerHistory(passport->getPassportNumber());
    EXPECT_EQ(hist.getFullName(), "Ivan Petrov");
    EXPECT_EQ(hist.getTicketNumbers().size(), 1);
    EXPECT_EQ(hist.getTicketNumbers()[0], "TK001");
}

TEST_F(PassengerManagerTest, GetPassengerHistoryThrowsIfNotFound) {
    EXPECT_THROW(manager->getPassengerHistory("NON_EXIST"), PassengerHistoryNotFound);
}
