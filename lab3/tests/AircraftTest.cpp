#include <gtest/gtest.h>
#include "Aircraft.h"
#include "Flight.h"

class AircraftTest : public ::testing::Test {
protected:
    AircraftModel* model;
    Aircraft* aircraft;

    void SetUp() override {
        model = new AircraftModel("Boeing 737", 180, "Boeing", 5000.0, 2500.0, "CFM56", 850);
        aircraft = new Aircraft("RA-82045", *model, 10000, AircraftStatus::Available, true);
    }

    void TearDown() override {
        delete model;
        delete aircraft;
    }
};

TEST_F(AircraftTest, ConstructorInitializesAllFieldsCorrectly) {
    EXPECT_EQ(aircraft->getTailNumber(), "RA-82045");
    EXPECT_EQ(aircraft->getFuelLevel(), 10000);
    EXPECT_EQ(aircraft->getStatus(), AircraftStatus::Available);
    EXPECT_TRUE(aircraft->getIsAvailable());

    const AircraftModel& m = aircraft->getModel();
    EXPECT_EQ(m.getModelName(), "Boeing 737");
    EXPECT_EQ(m.getManufacturer(), "Boeing");
    EXPECT_EQ(m.getCapacity(), 180);
    EXPECT_DOUBLE_EQ(m.getRangeKm(), 5000.0);
}

TEST_F(AircraftTest, SettersUpdateValuesCorrectly) {
    AircraftModel newModel("Airbus A320", 150, "Airbus", 6000.0, 2300.0, "CFM56", 870);
    aircraft->setTailNumber("RA-12345");
    aircraft->setModel(newModel);
    aircraft->setFuelLevel(8000);
    aircraft->setStatus(AircraftStatus::InFlight);
    aircraft->setIsAvailable(false);

    EXPECT_EQ(aircraft->getTailNumber(), "RA-12345");
    EXPECT_EQ(aircraft->getModel().getManufacturer(), "Airbus");
    EXPECT_EQ(aircraft->getFuelLevel(), 8000);
    EXPECT_EQ(aircraft->getStatus(), AircraftStatus::InFlight);
    EXPECT_FALSE(aircraft->getIsAvailable());
}

TEST_F(AircraftTest, RefuelIncreasesFuelLevel) {
    int initialFuel = aircraft->getFuelLevel();
    aircraft->refuel(500);
    EXPECT_EQ(aircraft->getFuelLevel(), initialFuel + 500);
}

TEST_F(AircraftTest, RefuelThrowsOnNonPositiveValues) {
    EXPECT_THROW(aircraft->refuel(0), InvalidFuelException);
    EXPECT_THROW(aircraft->refuel(-100), InvalidFuelException);
}

TEST_F(AircraftTest, AssignFlightUpdatesStatusAndAvailability) {
    time_t now = time(nullptr);
    Schedule schedule({ "SU100" }, now, now + 1000, now + 2000, now, false);
    AircraftModel m("Boeing 777", 400, "Boeing", 10000, 6000, "GE90", 900);
    Aircraft dummy("RA-00001", m, 5000, AircraftStatus::Available, true);
    Flight flight("SU100", "Москва", "Париж", dummy, schedule, 2500.0, {});

    aircraft->assignFlight(flight);

    EXPECT_EQ(aircraft->getStatus(), AircraftStatus::ScheduledForFlight);
    EXPECT_FALSE(aircraft->getIsAvailable());
}

TEST_F(AircraftTest, ScheduleMaintenanceChangesStatusAndReturnsValidSchedule) {
    Schedule maintenance = aircraft->scheduleMaintenance();

    EXPECT_EQ(aircraft->getStatus(), AircraftStatus::UnderMaintenance);
    EXPECT_FALSE(aircraft->getIsAvailable());

    time_t now = time(nullptr);
    EXPECT_GE(maintenance.getDepartureTime(), now);
    EXPECT_GE(maintenance.getArrivalTime(), maintenance.getDepartureTime());
}