#include <gtest/gtest.h>
#include "FlightManager.h"

class FlightManagerTest : public ::testing::Test {
protected:
    AircraftModel* model; Aircraft* aircraft1; Aircraft* aircraft2; Schedule* schedule1;
    Schedule* schedule2; Flight* flight1; Flight* flight2; FlightManager* manager;

    void SetUp() override {
        model = new AircraftModel("Airbus A320", 180, "Airbus", 6100.0, 2.5, "CFM56", 830);

        aircraft1 = new Aircraft("RA-12345", *model, 10000, AircraftStatus::Available, true);
        aircraft2 = new Aircraft("RA-67890", *model, 8000, AircraftStatus::UnderMaintenance, false);

        time_t departure = time(nullptr) + 3600;
        time_t arrival = departure + 7200; 
        schedule1 = new Schedule({}, departure, arrival, arrival + 1800, departure, false);
        schedule2 = new Schedule({}, departure + 86400, arrival + 86400, arrival + 90000, departure + 86400, false);

        vector<string> passengers = { "PSG001", "PSG002" };
        flight1 = new Flight("SU100", "Москва", "Париж", *aircraft1, *schedule1, 2500.0, passengers);
        flight2 = new Flight("SU200", "Берлин", "Рим", *aircraft2, *schedule2, 1800.0, passengers);

        vector<Flight> flights = { *flight1 };
        manager = new FlightManager(flights);
    }

    void TearDown() override {
        delete model; delete aircraft1; delete aircraft2; delete schedule1;
        delete schedule2; delete flight1; delete flight2; delete manager;
    }
};

TEST_F(FlightManagerTest, ConstructorInitializesCorrectly) {
    const auto& flights = manager->getFlights();
    ASSERT_EQ(flights.size(), 1);
    EXPECT_EQ(flights[0].getFlightNumber(), "SU100");
    EXPECT_EQ(flights[0].getOrigin(), "Москва");
    EXPECT_EQ(flights[0].getDestination(), "Париж");
}

TEST_F(FlightManagerTest, SetFlightsWorksCorrectly) {
    vector<Flight> newFlights = { *flight2 };
    manager->setFlights(newFlights);

    const auto& flights = manager->getFlights();
    ASSERT_EQ(flights.size(), 1);
    EXPECT_EQ(flights[0].getFlightNumber(), "SU200");
    EXPECT_EQ(flights[0].getDestination(), "Рим");
}

TEST_F(FlightManagerTest, CreateFlightAddsToList) {
    manager->createFlight(*flight2);

    const auto& flights = manager->getFlights();
    ASSERT_EQ(flights.size(), 2);
    EXPECT_EQ(flights.back().getFlightNumber(), "SU200");
}

TEST_F(FlightManagerTest, CancelFlightRemovesFromList) {
    manager->createFlight(*flight2);
    manager->cancelFlight("SU100");

    const auto& flights = manager->getFlights();
    ASSERT_EQ(flights.size(), 1);
    EXPECT_EQ(flights[0].getFlightNumber(), "SU200");
}

TEST_F(FlightManagerTest, CancelNonexistentFlightDoesNothing) {
    manager->cancelFlight("NONEXISTENT");
    const auto& flights = manager->getFlights();
    ASSERT_EQ(flights.size(), 1);
    EXPECT_EQ(flights[0].getFlightNumber(), "SU100");
}
