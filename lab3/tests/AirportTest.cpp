#include <gtest/gtest.h>
#include "Airport.h"

class AirportTest : public ::testing::Test {
protected:
    vector<Gate> gates; vector<Runway> runways; Airport* airport; Aircraft* aircraft;
    AircraftModel* model; Schedule* schedule; Flight* flight;

    void SetUp() override {
        gates = {
            Gate("A1", false, ""),
            Gate("A2", true, "SU100")
        };

        runways = {
            Runway("ВПП-1", true, 3000, RunwayStatus::Available),
            Runway("ВПП-2", false, 2500, RunwayStatus::Occupied)
        };

        airport = new Airport("Шереметьево", "Москва", runways, gates);

        model = new AircraftModel("Ту-154", 180, "Туполев", 3900, 2500, "НК-8", 900);
        aircraft = new Aircraft("RA-85555", *model, 4000, AircraftStatus::Available, true);

        time_t now = time(nullptr);
        schedule = new Schedule({ "SU321" }, now, now + 3600, now + 7200, now, false);

        flight = new Flight("SU321", "Москва", "Париж", *aircraft, *schedule, 2500, {});
    }

    void TearDown() override {
        delete airport; delete model; delete aircraft; delete schedule; delete flight;
    }
};

TEST_F(AirportTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(airport->getName(), "Шереметьево");
    EXPECT_EQ(airport->getLocation(), "Москва");
    EXPECT_EQ(airport->getRunways().size(), 2);
    EXPECT_EQ(airport->getGates().size(), 2);
}

TEST_F(AirportTest, SettersWorkCorrectly) {
    vector<Gate> newGates = { Gate("B1", false, "") };
    vector<Runway> newRunways = { Runway("ВПП-3", true, 3200, RunwayStatus::Available) };

    airport->setName("Домодедово");
    airport->setLocation("Москва");
    airport->setGates(newGates);
    airport->setRunways(newRunways);

    EXPECT_EQ(airport->getName(), "Домодедово");
    EXPECT_EQ(airport->getLocation(), "Москва");
    EXPECT_EQ(airport->getGates().size(), 1);
    EXPECT_EQ(airport->getRunways().size(), 1);
}

TEST_F(AirportTest, FindGateReturnsTrueIfGateExists) {
    EXPECT_TRUE(airport->findGate("A1"));
}

TEST_F(AirportTest, FindGateReturnsFalseIfGateDoesNotExist) {
    EXPECT_FALSE(airport->findGate("Z9"));
}

TEST_F(AirportTest, AssignGateAssignsFirstFreeGateToFlight) {
    airport->assignGate(*flight);

    const auto& gates = airport->getGates();
    EXPECT_TRUE(gates[0].getIsOccupied());
    EXPECT_EQ(gates[0].getAssignedFlightNumber(), "SU321");
}

TEST_F(AirportTest, AssignGateDoesNothingIfAllOccupied) {
    vector<Gate> busyGates = {
        Gate("B1", true, "SU111"),
        Gate("B2", true, "SU222")
    };
    vector<Runway> dummyRunways;
    Airport fullAirport("Пулково", "Санкт-Петербург", dummyRunways, busyGates);

    fullAirport.assignGate(*flight);

    EXPECT_EQ(fullAirport.getGates()[0].getAssignedFlightNumber(), "SU111");
    EXPECT_EQ(fullAirport.getGates()[1].getAssignedFlightNumber(), "SU222");
}

TEST_F(AirportTest, AssignRunwayReservesFirstAvailableRunway) {
    airport->assignRunwayToFlight(*flight);

    const auto& runways = airport->getRunways();
    EXPECT_FALSE(runways[0].getIsAvailable());
    EXPECT_EQ(runways[0].getStatus(), RunwayStatus::Reserved);
}

TEST_F(AirportTest, AssignRunwayDoesNothingIfAllOccupied) {
    vector<Runway> occupiedRunways = {
        Runway("ВПП-5", false, 2500, RunwayStatus::Occupied)
    };
    vector<Gate> dummyGates;
    Airport busyAirport("Кольцово", "Екатеринбург", occupiedRunways, dummyGates);

    busyAirport.assignRunwayToFlight(*flight);

    EXPECT_EQ(busyAirport.getRunways()[0].getStatus(), RunwayStatus::Occupied);
    EXPECT_FALSE(busyAirport.getRunways()[0].getIsAvailable());
}
