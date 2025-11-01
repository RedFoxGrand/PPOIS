#include "gtest/gtest.h"
#include "Booking.h"

using namespace std;

class BookingTest : public ::testing::Test {
protected:
    ContactInfo* contact; Visa* visa; Passport* passport; Passenger* passenger; AircraftModel* model;
    Aircraft* aircraft; Schedule* schedule; Flight* flight; Seat* seat; Fare* fare;
    Ticket* ticket; PaymentCard* card; Account* account; vector<Ticket> tickets; Booking* booking;

    void SetUp() override {
        time_t now = time(nullptr);

        contact = new ContactInfo("user@mail.com", "+79991234567", "Россия");
        visa = new Visa("VS001", "Франция", now - 100000, now + 100000, VisaType::Tourist);
        passport = new Passport("P1234567", "Россия", "Иван Иванов", now - 200000, now + 200000, *visa, MaritalStatus::NotMarried);
        passenger = new Passenger("Иван", "Иванов", now - 800000000, *contact, "PID001", *passport);

        model = new AircraftModel("Boeing 737", 180, "Boeing", 7000, 2500, "CFM", 850);
        aircraft = new Aircraft("RA-89001", *model, 2015, AircraftStatus::Available, true);
        schedule = new Schedule({}, now + 10000, now + 20000, now + 25000, now + 30000, false);
        flight = new Flight("SU123", "Москва", "Париж", *aircraft, *schedule, 25000.0, { "PID001" });

        seat = new Seat("14A", false, true, SeatClassType::Economy);
        fare = new Fare("F001", 25000.0, FareClass::Economy, "5%", "0%");
        ticket = new Ticket("TICK001", *passenger, "PID001", *flight, "SU123", *seat, *fare);
        tickets.push_back(*ticket);

        card = new PaymentCard("ACC001", "4000123412341234", "Иван Иванов", "12/28", 123);
        account = new Account(*passenger, *card, "RU001122334455", "SberBank", 100000.0, "RUB");

        booking = new Booking("BKG001", *passenger, *flight, false, tickets, BookingStatus::Pending);
    }

    void TearDown() override {
        delete booking; delete account; delete card; delete ticket; delete fare; delete seat;
        delete flight; delete schedule;  delete aircraft; delete model;
        delete passenger; delete passport; delete visa; delete contact;
    }
};

TEST_F(BookingTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(booking->getBookingId(), "BKG001");
    EXPECT_EQ(booking->getPassenger().getName(), "Иван");
    EXPECT_EQ(booking->getFlight().getFlightNumber(), "SU123");
    EXPECT_FALSE(booking->isPaidStatus());
    EXPECT_EQ(booking->getTickets().size(), 1);
    EXPECT_EQ(booking->getStatus(), BookingStatus::Pending);
}

TEST_F(BookingTest, SettersModifyDataCorrectly) {
    booking->setBookingId("NEWID");
    booking->setPaid(true);
    booking->setStatus(BookingStatus::CheckedIn);

    EXPECT_EQ(booking->getBookingId(), "NEWID");
    EXPECT_TRUE(booking->isPaidStatus());
    EXPECT_EQ(booking->getStatus(), BookingStatus::CheckedIn);
}

TEST_F(BookingTest, ConfirmPaymentSuccess) {
    double initialBalance = account->getBalance();
    booking->confirmPayment(*account, 25000.0);

    EXPECT_TRUE(booking->isPaidStatus());
    EXPECT_EQ(booking->getStatus(), BookingStatus::Confirmed);
    EXPECT_NEAR(account->getBalance(), initialBalance - 25000.0, 1e-6);
}

TEST_F(BookingTest, ConfirmPaymentThrowsIfInsufficientFunds) {
    EXPECT_THROW(booking->confirmPayment(*account, 9999999.0), InvalidBalanceException);
}

TEST_F(BookingTest, CancelBookingChangesStatus) {
    booking->cancel();
    EXPECT_EQ(booking->getStatus(), BookingStatus::Cancelled);
}

TEST_F(BookingTest, CancelTwiceThrowsException) {
    booking->cancel();
    EXPECT_THROW(booking->cancel(), InvalidStatusException);
}