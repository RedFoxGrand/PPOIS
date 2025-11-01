#include <gtest/gtest.h>
#include "Passenger.h"

class PassengerTest : public ::testing::Test {
protected:
    ContactInfo* contact; Visa* visa; Passport* passport;
    Passenger* passenger; time_t birthDate; time_t issueDate; time_t expiryDate;

    void SetUp() override {
        birthDate = time(nullptr) - 86400 * 365 * 25;
        issueDate = time(nullptr) - 86400 * 100;
        expiryDate = time(nullptr) + 86400 * 365;

        contact = new ContactInfo("test@mail.com", "+79001234567", "Moscow, Russia");
        visa = new Visa("V555", "Japan", issueDate, expiryDate, VisaType::Tourist);
        passport = new Passport("P123456", "Russia", "Ivan Petrov", issueDate, expiryDate, *visa, MaritalStatus::NotMarried);

        passenger = new Passenger("Ivan", "Petrov", birthDate, *contact, "PSG001", *passport);
    }

    void TearDown() override {
        delete contact; delete visa; delete passport; delete passenger;
    }
};

TEST_F(PassengerTest, ConstructorInitializesAllFieldsCorrectly) {
    EXPECT_EQ(passenger->getName(), "Ivan");
    EXPECT_EQ(passenger->getSurname(), "Petrov");
    EXPECT_EQ(passenger->getPassengerId(), "PSG001");

    const ContactInfo& ci = passenger->getContactInfo();
    EXPECT_EQ(ci.getEmail(), "test@mail.com");
    EXPECT_EQ(ci.getPhone(), "+79001234567");
    EXPECT_EQ(ci.getAddress(), "Moscow, Russia");

    const Passport& pp = passenger->getPassport();
    EXPECT_EQ(pp.getPassportNumber(), "P123456");
    EXPECT_EQ(pp.getCountry(), "Russia");
    EXPECT_EQ(pp.getHolderName(), "Ivan Petrov");
    EXPECT_EQ(pp.getVisa().getCountry(), "Japan");
    EXPECT_EQ(pp.getVisa().getType(), VisaType::Tourist);
}
TEST_F(PassengerTest, SettersUpdateFieldsCorrectly) {
    Passport newPassport("P999", "USA", "John Doe", issueDate, expiryDate, *visa, MaritalStatus::Married);
    passenger->setPassengerId("NEW001");
    passenger->setPassport(newPassport);

    EXPECT_EQ(passenger->getPassengerId(), "NEW001");
    EXPECT_EQ(passenger->getPassport().getCountry(), "USA");
    EXPECT_EQ(passenger->getPassport().getMaritalStatus(), MaritalStatus::Married);

    vector<string> tickets = { "TKT1", "TKT2" };
    passenger->setTicketNumbers(tickets);
    EXPECT_EQ(passenger->getTicketNumbers().size(), 2);
    EXPECT_EQ(passenger->getTicketNumbers()[0], "TKT1");
}

TEST_F(PassengerTest, AddTicketAddsTicketCorrectly) {
    passenger->addTicket("T100");
    passenger->addTicket("T200");

    const vector<string>& tickets = passenger->getTicketNumbers();
    EXPECT_EQ(tickets.size(), 2);
    EXPECT_EQ(tickets[0], "T100");
    EXPECT_EQ(tickets[1], "T200");
}