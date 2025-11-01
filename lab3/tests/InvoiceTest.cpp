#include "gtest/gtest.h"
#include "Invoice.h"

class InvoiceTest : public ::testing::Test {
protected:
    ContactInfo* contact; Visa* visa; Passport* passport;
    Passenger* passenger; Invoice* invoice; time_t now;

    void SetUp() override {
        now = time(nullptr);

        contact = new ContactInfo("ivanov@example.com", "+79998887766", "Россия, Москва");
        visa = new Visa("V001", "Франция", now - 100000, now + 100000, VisaType::Tourist);
        passport = new Passport("PP123456", "Россия", "Сергей Иванов", now - 500000, now + 500000, *visa, MaritalStatus::Married);
        passenger = new Passenger("Сергей", "Иванов", now - 1000000000, *contact, "P001", *passport);
        invoice = new Invoice("INV001", *passenger, 25000.50, now, false);
    }

    void TearDown() override {
        delete contact; delete visa; delete passport; delete passenger; delete invoice;
    }
};

TEST_F(InvoiceTest, ConstructorSetsFieldsCorrectly) {
    EXPECT_EQ(invoice->getInvoiceNumber(), "INV001");
    EXPECT_EQ(invoice->getPassenger().getPassengerId(), "P001");
    EXPECT_DOUBLE_EQ(invoice->getTotalAmount(), 25000.50);
    EXPECT_EQ(invoice->getTimestamp(), now);
    EXPECT_FALSE(invoice->getIsPaid());
}

TEST_F(InvoiceTest, SettersWorkCorrectly) {
    time_t newTime = now + 10000;
    invoice->setInvoiceNumber("INV002");
    invoice->setTotalAmount(9999.99);
    invoice->setTimestamp(newTime);
    invoice->setIsPaid(true);

    EXPECT_EQ(invoice->getInvoiceNumber(), "INV002");
    EXPECT_DOUBLE_EQ(invoice->getTotalAmount(), 9999.99);
    EXPECT_EQ(invoice->getTimestamp(), newTime);
    EXPECT_TRUE(invoice->getIsPaid());
}

TEST_F(InvoiceTest, SetPassengerUpdatesCorrectly) {
    ContactInfo contact2("petrov@example.com", "+79991234567", "Россия, Санкт-Петербург");
    Visa visa2("V002", "Италия", now - 200000, now + 300000, VisaType::Business);
    Passport passport2("PP654321", "Россия", "Андрей Петров", now - 800000, now + 900000, visa2, MaritalStatus::NotMarried);
    Passenger passenger2("Андрей", "Петров", now - 900000000, contact2, "P002", passport2);

    invoice->setPassenger(passenger2);
    EXPECT_EQ(invoice->getPassenger().getPassengerId(), "P002");
    EXPECT_EQ(invoice->getPassenger().getFullName(), "Андрей Петров");
}

TEST_F(InvoiceTest, MarkPaidChangesStatusToTrue) {
    EXPECT_FALSE(invoice->getIsPaid());
    invoice->markPaid();
    EXPECT_TRUE(invoice->getIsPaid());
}

TEST_F(InvoiceTest, MarkPaidDoesNotChangeIfAlreadyPaid) {
    invoice->setIsPaid(true);
    invoice->markPaid();
    EXPECT_TRUE(invoice->getIsPaid());
}

