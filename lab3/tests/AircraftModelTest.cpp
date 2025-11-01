#include <gtest/gtest.h>
#include "AircraftModel.h"

using namespace std;

class AircraftModelTest : public ::testing::Test {
protected:
    AircraftModel* aircraft;

    void SetUp() override {
        aircraft = new AircraftModel( "Boeing 737", 180, "Boeing", 5000.0, 2600.0, "CFM56", 850);
    }

    void TearDown() override {
        delete aircraft;
    }
};

TEST_F(AircraftModelTest, ConstructorInitializesValuesCorrectly) {
    EXPECT_EQ(aircraft->getModelName(), "Boeing 737");
    EXPECT_EQ(aircraft->getCapacity(), 180);
    EXPECT_EQ(aircraft->getManufacturer(), "Boeing");
    EXPECT_DOUBLE_EQ(aircraft->getRangeKm(), 5000.0);
    EXPECT_DOUBLE_EQ(aircraft->getFuelConsumption(), 2600.0);
    EXPECT_EQ(aircraft->getEngineType(), "CFM56");
    EXPECT_EQ(aircraft->getSpeed(), 850);
}

TEST_F(AircraftModelTest, SettersUpdateFieldsCorrectly) {
    aircraft->setModelName("Airbus A320");
    aircraft->setCapacity(150);
    aircraft->setManufacturer("Airbus");
    aircraft->setRangeKm(6100.5);
    aircraft->setFuelConsumption(2500.2);
    aircraft->setEngineType("IAE V2500");
    aircraft->setSpeed(830);

    EXPECT_EQ(aircraft->getModelName(), "Airbus A320");
    EXPECT_EQ(aircraft->getCapacity(), 150);
    EXPECT_EQ(aircraft->getManufacturer(), "Airbus");
    EXPECT_DOUBLE_EQ(aircraft->getRangeKm(), 6100.5);
    EXPECT_DOUBLE_EQ(aircraft->getFuelConsumption(), 2500.2);
    EXPECT_EQ(aircraft->getEngineType(), "IAE V2500");
    EXPECT_EQ(aircraft->getSpeed(), 830);
}

TEST_F(AircraftModelTest, EstimateRangeCalculatesCorrectly) {
    EXPECT_DOUBLE_EQ(aircraft->estimateRange(), 4740.0);
}

TEST_F(AircraftModelTest, EstimateRangeReturnsZeroIfFuelTooHigh) {
    aircraft->setFuelConsumption(60000.0);
    aircraft->setRangeKm(2000.0);
    EXPECT_DOUBLE_EQ(aircraft->estimateRange(), 0.0);
}

TEST_F(AircraftModelTest, HandlesExtremeValuesGracefully) {
    aircraft->setFuelConsumption(0.0);
    EXPECT_DOUBLE_EQ(aircraft->estimateRange(), 5000.0);

    aircraft->setFuelConsumption(10000.0);
    EXPECT_GE(aircraft->estimateRange(), 0.0);
}
