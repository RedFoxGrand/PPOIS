#include <gtest/gtest.h>
#include "FuelRecord.h"

class FuelRecordTest : public ::testing::Test {
protected:
    AircraftModel* model; Aircraft* aircraft;
    FuelRecord* record; time_t now;

    void SetUp() override {
        now = time(nullptr);
        model = new AircraftModel("Airbus A320", 180, "Airbus", 6100.0, 2400.0, "CFM56", 840);
        aircraft = new Aircraft("RA-32001", *model, 4000, AircraftStatus::Available, true);
        record = new FuelRecord("REF001", *aircraft, 2000.0, now);
    }

    void TearDown() override {
        delete model;
        delete aircraft;
        delete record;
    }
};

TEST_F(FuelRecordTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(record->getRefuelId(), "REF001");
    EXPECT_EQ(record->getAircraft().getTailNumber(), "RA-32001");
    EXPECT_DOUBLE_EQ(record->getLiters(), 2000.0);
    EXPECT_LE(record->getTimestamp(), time(nullptr));
}

TEST_F(FuelRecordTest, SettersWorkCorrectly) {
    AircraftModel newModel("Boeing 777", 350, "Boeing", 10000.0, 5000.0, "GE90", 900);
    Aircraft newAircraft("RA-77777", newModel, 8000, AircraftStatus::Available, true);
    time_t newTime = time(nullptr) - 3600;

    record->setRefuelId("REF999");
    record->setAircraft(newAircraft);
    record->setLiters(5000.0);
    record->setTimestamp(newTime);

    EXPECT_EQ(record->getRefuelId(), "REF999");
    EXPECT_EQ(record->getAircraft().getTailNumber(), "RA-77777");
    EXPECT_DOUBLE_EQ(record->getLiters(), 5000.0);
    EXPECT_EQ(record->getTimestamp(), newTime);
}

TEST_F(FuelRecordTest, AddFuelIncreasesLitersAndUpdatesTimestamp) {
    double oldLiters = record->getLiters();
    time_t oldTime = record->getTimestamp();

    record->addFuel(300.0);

    EXPECT_DOUBLE_EQ(record->getLiters(), oldLiters + 300.0);
    EXPECT_GE(record->getTimestamp(), oldTime);
}

TEST_F(FuelRecordTest, AddFuelThrowsIfNegativeOrZero) {
    EXPECT_THROW(record->addFuel(-100.0), InvalidFuelException);
    EXPECT_THROW(record->addFuel(0.0), InvalidFuelException);
}

TEST_F(FuelRecordTest, AssociatedAircraftRemainsUnchanged) {
    const Aircraft& a = record->getAircraft();
    EXPECT_EQ(a.getModel().getManufacturer(), "Airbus");
    EXPECT_EQ(a.getModel().getModelName(), "Airbus A320");
    EXPECT_EQ(a.getFuelLevel(), 4000);
}
