#include <gtest/gtest.h>
#include "BookingManager.h"

class BookingManagerTest : public ::testing::Test {
protected:
    ContactInfo* contact; Visa* visa; Passport* passport; Passenger* passenger1; Passenger* passenger2;
    AircraftModel* model; Aircraft* aircraft; Schedule* schedule; Flight* flight; Seat* seat; Fare* fare;
    Ticket* ticket1; Ticket* ticket2; Booking* booking1; Booking* booking2;
    BookingManager* manager; time_t birthDate; time_t issueDate; time_t expiryDate;

    void SetUp() override {
        birthDate = time(nullptr) - 86400 * 365 * 30;
        issueDate = time(nullptr) - 86400 * 100;
        expiryDate = time(nullptr) + 86400 * 365;

        contact = new ContactInfo("test@mail.com", "+79001234567", "Moscow, Russia");
        visa = new Visa("VISA001", "France", issueDate, expiryDate, VisaType::Tourist);
        passport = new Passport("P123456", "Russia", "Ivan Petrov", issueDate, expiryDate, *visa, MaritalStatus::NotMarried);

        passenger1 = new Passenger("Ivan", "Petrov", birthDate, *contact, "PSG001", *passport);
        passenger2 = new Passenger("Petr", "Sidorov", birthDate, *contact, "PSG002", *passport);

        model = new AircraftModel("Airbus A320", 180, "Airbus", 6000, 2600, "CFM56", 850);
        aircraft = new Aircraft("RA-12345", *model, 5000, AircraftStatus::Available, true);

        schedule = new Schedule({}, issueDate, expiryDate, expiryDate + 3600, issueDate, true);
        flight = new Flight("SU100", "Moscow", "Paris", *aircraft, *schedule, 25000.0, {});

        seat = new Seat("12A", false, true, SeatClassType::Economy);
        fare = new Fare("ECON01", 20000.0, FareClass::Economy, "VAT", "No");

        ticket1 = new Ticket("TCK001", *passenger1, passenger1->getPassengerId(), *flight, "SU100", *seat, *fare);
        ticket2 = new Ticket("TCK002", *passenger2, passenger2->getPassengerId(), *flight, "SU100", *seat, *fare);

        booking1 = new Booking("BK001", *passenger1, *flight, false, std::vector<Ticket>{*ticket1}, BookingStatus::Pending);
        booking2 = new Booking("BK002", *passenger2, *flight, false, std::vector<Ticket>{*ticket2}, BookingStatus::Pending);

        manager = new BookingManager({ *booking1, *booking2 });
    }

    void TearDown() override {
        delete contact; delete visa; delete passport; delete passenger1; delete passenger2; delete model;
        delete aircraft; delete schedule; delete flight; delete seat; delete fare;
        delete ticket1; delete ticket2; delete booking1; delete booking2; delete manager;
    }
};

TEST_F(BookingManagerTest, ConstructorAndGetSetBookings) {
    EXPECT_EQ(manager->getBookings().size(), 2);
    EXPECT_EQ(manager->getBookings()[0].getBookingId(), "BK001");

    BookingManager newManager;
    newManager.setBookings(manager->getBookings());
    EXPECT_EQ(newManager.getBookings().size(), 2);
}

TEST_F(BookingManagerTest, FindByPassengerReturnsCorrectBooking) {
    Booking* found = manager->findByPassenger("PSG001");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getBookingId(), "BK001");
}

TEST_F(BookingManagerTest, FindByPassengerReturnsNullptrIfNotFound) {
    Booking* found = manager->findByPassenger("UNKNOWN");
    EXPECT_EQ(found, nullptr);
}

TEST_F(BookingManagerTest, ModifyBookingChangesStatusToConfirmed) {
    Booking* modified = manager->modifyBooking("BK001");
    ASSERT_NE(modified, nullptr);
    EXPECT_EQ(modified->getStatus(), BookingStatus::Confirmed);
}

TEST_F(BookingManagerTest, ModifyBookingReturnsNullptrIfNotFound) {
    Booking* modified = manager->modifyBooking("NOBOOK");
    EXPECT_EQ(modified, nullptr);
}
