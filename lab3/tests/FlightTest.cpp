#include <gtest/gtest.h>
#include "Flight.h"

class FlightTest : public ::testing::Test {
protected:
    AircraftModel* model; Aircraft* aircraft;
    Schedule* schedule; Flight* flight;

    void SetUp() override {
        model = new AircraftModel("Boeing 787", 300, "Boeing", 15000, 8000, "Trent 1000", 900);
        aircraft = new Aircraft("RA-11111", *model, 12000, AircraftStatus::Available, true);
        time_t now = time(nullptr);
        schedule = new Schedule({ "SU101" }, now, now + 3600, now + 7200, now, false);
        flight = new Flight("SU101", "Moscow", "New York", *aircraft, *schedule, 7500.0, { "P1", "P2" });
    }

    void TearDown() override {
        delete model; delete aircraft;
        delete schedule; delete flight;
    }
};

TEST_F(FlightTest, ConstructorInitializesAllFields) {
    EXPECT_EQ(flight->getFlightNumber(), "SU101");
    EXPECT_EQ(flight->getOrigin(), "Moscow");
    EXPECT_EQ(flight->getDestination(), "New York");
    EXPECT_EQ(flight->getDistanceKm(), 7500.0);
    EXPECT_EQ(flight->getPassengerIds().size(), 2);
}

TEST_F(FlightTest, SettersWorkCorrectly) {
    AircraftModel model2("Airbus A330", 260, "Airbus", 12000, 7000, "RR Trent", 880);
    Aircraft a2("RA-22222", model2, 9000, AircraftStatus::Available, true);
    time_t now = time(nullptr);
    Schedule s2({ "SU222" }, now, now + 4000, now + 8000, now, false);
    vector<string> passengers = { "P3", "P4", "P5" };

    flight->setFlightNumber("SU222");
    flight->setOrigin("Paris");
    flight->setDestination("Tokyo");
    flight->setAircraft(a2);
    flight->setSchedule(s2);
    flight->setDistanceKm(9700);
    flight->setPassengerIds(passengers);

    EXPECT_EQ(flight->getFlightNumber(), "SU222");
    EXPECT_EQ(flight->getOrigin(), "Paris");
    EXPECT_EQ(flight->getDestination(), "Tokyo");
    EXPECT_EQ(flight->getAircraft().getTailNumber(), "RA-22222");
    EXPECT_EQ(flight->getSchedule().getFlightNumbers().size(), 1);
    EXPECT_EQ(flight->getDistanceKm(), 9700);
    EXPECT_EQ(flight->getPassengerIds().size(), 3);
}

TEST_F(FlightTest, AddPassengerAddsToList) {
    size_t before = flight->getPassengerIds().size();
    flight->addPassenger("P3");
    EXPECT_EQ(flight->getPassengerIds().size(), before + 1);
    EXPECT_EQ(flight->getPassengerIds().back(), "P3");
}

TEST_F(FlightTest, CalculateFlightTimeReturnsCorrectValue) {
    double expectedHours = 7500.0 / 900.0;
    EXPECT_NEAR(flight->calculateFlightTime(*model), expectedHours, 1e-6);
}

TEST_F(FlightTest, CalculateFlightTimeReturnsZeroForInvalidSpeed) {
    AircraftModel broken("BrokenJet", 10, "Test", 1000, 100, "FailEngine", 0);
    EXPECT_DOUBLE_EQ(flight->calculateFlightTime(broken), 0.0);
}