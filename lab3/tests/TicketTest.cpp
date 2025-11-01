#include <gtest/gtest.h>
#include "Ticket.h"

class TicketTest : public ::testing::Test {
protected:
    ContactInfo* contact; Visa* visa; Passport* passport; Passenger* passenger; Fare* fare;
    Seat* seat; AircraftModel* model; Aircraft* aircraft; Schedule* schedule;
    Flight* flight; Ticket* ticket; time_t birthDate; time_t issueDate; time_t expiryDate;

    void SetUp() override {
        birthDate = time(nullptr) - 86400 * 365 * 25;
        issueDate = time(nullptr) - 86400 * 100;
        expiryDate = time(nullptr) + 86400 * 365;

        contact = new ContactInfo("test@mail.com", "+79001112233", "Moscow, Russia");
        visa = new Visa("VS123", "Germany", issueDate, expiryDate, VisaType::Tourist);
        passport = new Passport("PP123456", "Russia", "Ivan Ivanov", issueDate, expiryDate, *visa, MaritalStatus::NotMarried);
        passenger = new Passenger("Ivan", "Ivanov", birthDate, *contact, "P001", *passport);

        model = new AircraftModel("Boeing 737", 180, "Boeing", 4000.0, 2500.0, "CFM56", 850);
        aircraft = new Aircraft("RA-89001", *model, 5000, AircraftStatus::Available, true);

        time_t now = time(nullptr);
        schedule = new Schedule({}, now, now + 3600, now + 7200, now, false);
        flight = new Flight("SU123", "Moscow", "Berlin", *aircraft, *schedule, 1600.0, { "P001" });

        seat = new Seat("12A", false, true, SeatClassType::Economy);
        fare = new Fare("EC100", 15000.0, FareClass::Economy, "VAT 20%", "No discounts");

        ticket = new Ticket("TK12345", *passenger, "P001", *flight, "SU123", *seat, *fare);
    }

    void TearDown() override {
        delete contact; delete visa; delete passport; delete passenger; delete model; delete aircraft;
        delete schedule; delete flight; delete seat; delete fare; delete ticket;
    }
};

TEST_F(TicketTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(ticket->getTicketNumber(), "TK12345");
    EXPECT_EQ(ticket->getPassenger().getPassengerId(), "P001");
    EXPECT_EQ(ticket->getPassenger().getName(), "Ivan");
    EXPECT_EQ(ticket->getFlightNumber(), "SU123");
    EXPECT_EQ(ticket->getSeat().getSeatNumber(), "12A");
    EXPECT_DOUBLE_EQ(ticket->getFare().getPrice(), 15000.0);
}

TEST_F(TicketTest, SettersWorkCorrectly) {
    Passenger newPassenger("Petr", "Sidorov", birthDate, *contact, "P002", *passport);
    Seat newSeat("5C", false, true, SeatClassType::Business);
    Fare newFare("BUS200", 45000.0, FareClass::Business, "VAT 20%", "Discount 10%");
    AircraftModel newModel("Airbus A320", 190, "Airbus", 4200.0, 2600.0, "IAE V2500", 870);
    Aircraft newAircraft("RA-89002", newModel, 4000, AircraftStatus::Available, true);
    time_t now = time(nullptr);
    Schedule newSchedule({}, now, now + 7200, now + 10800, now, false);
    Flight newFlight("S7200", "Moscow", "Paris", newAircraft, newSchedule, 2500.0, { "P002" });

    ticket->setTicketNumber("TK99999");
    ticket->setPassenger(newPassenger);
    ticket->setPassengerId("P002");
    ticket->setFlight(newFlight);
    ticket->setFlightNumber("S7200");
    ticket->setSeat(newSeat);
    ticket->setFare(newFare);

    EXPECT_EQ(ticket->getTicketNumber(), "TK99999");
    EXPECT_EQ(ticket->getPassenger().getPassengerId(), "P002");
    EXPECT_EQ(ticket->getPassenger().getSurname(), "Sidorov");
    EXPECT_EQ(ticket->getFlightNumber(), "S7200");
    EXPECT_EQ(ticket->getSeat().getSeatNumber(), "5C");
    EXPECT_DOUBLE_EQ(ticket->getFare().getPrice(), 45000.0);
}

TEST_F(TicketTest, ChangeSeatUpdatesSeatCorrectly) {
    Seat newSeat("10B", false, true, SeatClassType::Premium);
    ticket->changeSeat(newSeat);
    EXPECT_EQ(ticket->getSeat().getSeatNumber(), "10B");
}

TEST_F(TicketTest, FlightDataCorrect) {
    EXPECT_EQ(ticket->getFlight().getOrigin(), "Moscow");
    EXPECT_EQ(ticket->getFlight().getDestination(), "Berlin");
    EXPECT_DOUBLE_EQ(ticket->getFlight().getDistanceKm(), 1600.0);
}

TEST_F(TicketTest, FareCalculatesTotalCorrectly) {
    double total = ticket->getFare().calculateTotal(10.0); 
    EXPECT_DOUBLE_EQ(total, 16500.0);
}

TEST_F(TicketTest, FareAppliesDiscountCorrectly) {
    Fare discountFare("DISC1", 10000.0, FareClass::Economy, "VAT", "10%");
    discountFare.applyDiscount(10.0);
    EXPECT_DOUBLE_EQ(discountFare.getPrice(), 9000.0);
}

TEST_F(TicketTest, FareRefundableCheck) {
    EXPECT_FALSE(ticket->getFare().isRefundable()); 

    Fare businessFare("BUS500", 30000.0, FareClass::Business, "VAT", "None");
    ticket->setFare(businessFare);

    EXPECT_TRUE(ticket->getFare().isRefundable());
}
