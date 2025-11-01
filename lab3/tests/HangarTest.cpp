#include <gtest/gtest.h>
#include "Hangar.h"

class HangarTest : public ::testing::Test {
protected:
    AircraftModel* model; Aircraft* aircraft1; Aircraft* aircraft2;
    Aircraft* aircraft3; Hangar* hangar;

    void SetUp() override {
        model = new AircraftModel("Boeing 737", 180, "Boeing", 5000.0, 2500.0, "Jet", 850);

        aircraft1 = new Aircraft("RA-12345", *model, 5000, AircraftStatus::Available, true);
        aircraft2 = new Aircraft("RA-67890", *model, 6000, AircraftStatus::Available, true);
        aircraft3 = new Aircraft("RA-11111", *model, 7000, AircraftStatus::Available, true);

        hangar = new Hangar("Москва-Шереметьево", 2, false, {});
    }

    void TearDown() override {
        delete model;
        delete aircraft1;
        delete aircraft2;
        delete aircraft3;
        delete hangar;
    }
};

TEST_F(HangarTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(hangar->getLocation(), "Москва-Шереметьево");
    EXPECT_EQ(hangar->getCapacity(), 2);
    EXPECT_FALSE(hangar->getIsOccupied());
    EXPECT_TRUE(hangar->getStoredAircraft().empty());
}

TEST_F(HangarTest, SettersWorkCorrectly) {
    hangar->setLocation("Домодедово");
    hangar->setCapacity(3);
    hangar->setOccupied(true);

    std::vector<Aircraft> list = { *aircraft1, *aircraft2 };
    hangar->setStoredAircraft(list);

    EXPECT_EQ(hangar->getLocation(), "Домодедово");
    EXPECT_EQ(hangar->getCapacity(), 3);
    EXPECT_TRUE(hangar->getIsOccupied());
    EXPECT_EQ(hangar->getStoredAircraft().size(), 2);
}

TEST_F(HangarTest, StoreAircraftAddsPlane) {
    hangar->storeAircraft(*aircraft1);
    EXPECT_EQ(hangar->getStoredAircraft().size(), 1);
    EXPECT_TRUE(hangar->getIsOccupied());
}

TEST_F(HangarTest, StoreAircraftThrowsIfFull) {
    hangar->storeAircraft(*aircraft1);
    hangar->storeAircraft(*aircraft2);
    EXPECT_THROW(hangar->storeAircraft(*aircraft3), InvalidCapacityException);
}

TEST_F(HangarTest, ReleaseAircraftRemovesPlane) {
    hangar->storeAircraft(*aircraft1);
    hangar->storeAircraft(*aircraft2);
    hangar->releaseAircraft(*aircraft1);

    EXPECT_EQ(hangar->getStoredAircraft().size(), 1);
    EXPECT_TRUE(hangar->getIsOccupied());
}

TEST_F(HangarTest, ReleaseAircraftSetsOccupiedFalseWhenEmpty) {
    hangar->storeAircraft(*aircraft1);
    hangar->releaseAircraft(*aircraft1);

    EXPECT_TRUE(hangar->getStoredAircraft().empty());
    EXPECT_FALSE(hangar->getIsOccupied());
}

TEST_F(HangarTest, CannotExceedCapacityAfterMultipleOperations) {
    hangar->storeAircraft(*aircraft1);
    hangar->storeAircraft(*aircraft2);
    EXPECT_THROW(hangar->storeAircraft(*aircraft3), InvalidCapacityException);

    hangar->releaseAircraft(*aircraft1);
    EXPECT_NO_THROW(hangar->storeAircraft(*aircraft3));
    EXPECT_EQ(hangar->getStoredAircraft().size(), 2);
}
