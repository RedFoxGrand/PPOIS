#include <gtest/gtest.h>
#include "FlightPlan.h"

using namespace std;

class FlightPlanTest : public ::testing::Test {
protected:
    AircraftModel* model; Aircraft* aircraft; Schedule* schedule; Flight* flight;
    WeatherCondition* weather; Airport* airport1; Airport* airport2; FlightPlan* plan;

    void SetUp() override {
        model = new AircraftModel("Airbus A320", 180, "Airbus", 6100.0, 2.4, "CFM56", 840);
        aircraft = new Aircraft("RA-32100", *model, 11000, AircraftStatus::Available, true);

        time_t departure = time(nullptr) + 3600;
        time_t arrival = departure + 7200;
        schedule = new Schedule({}, departure, arrival, arrival + 1800, departure, false);

        vector<string> passengers = { "PSG001", "PSG002" };
        flight = new Flight("SU100", "Москва", "Париж", *aircraft, *schedule, 2500.0, passengers);

        weather = new WeatherCondition("Москва", "Ясно", "Низкий", 19.0, 8.0);

        vector<Runway> runways = {
            Runway("R1", true, 3200.0, RunwayStatus::Available),
            Runway("R2", true, 3700.0, RunwayStatus::Available)
        };
        vector<Gate> gates = {
            Gate("A1", false, ""),
            Gate("B1", false, "")
        };

        airport1 = new Airport("Шереметьево", "Москва", runways, gates);
        airport2 = new Airport("Шарль-де-Голль", "Париж", runways, gates);

        vector<Airport> checkpoints = { *airport1, *airport2 };
        plan = new FlightPlan(*flight, checkpoints, *weather, 33000);
    }

    void TearDown() override {
        delete model; delete aircraft; delete schedule; delete flight;
        delete weather; delete airport1; delete airport2; delete plan;
    }
};

TEST_F(FlightPlanTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(plan->getFlight().getFlightNumber(), "SU100");
    EXPECT_EQ(plan->getFlight().getOrigin(), "Москва");
    EXPECT_EQ(plan->getFlight().getDestination(), "Париж");
    EXPECT_EQ(plan->getCheckpoints().size(), 2);
    EXPECT_EQ(plan->getWeather().getCondition(), "Ясно");
    EXPECT_EQ(plan->getAltitude(), 33000);
}

TEST_F(FlightPlanTest, SettersWorkCorrectly) {
    WeatherCondition newWeather("Париж", "Дождь", "Средний", 15.0, 25.0);
    plan->setWeather(newWeather);
    plan->setAltitude(28000);

    EXPECT_EQ(plan->getWeather().getCondition(), "Дождь");
    EXPECT_EQ(plan->getWeather().getLocation(), "Париж");
    EXPECT_EQ(plan->getAltitude(), 28000);
}