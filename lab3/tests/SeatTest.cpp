#include <gtest/gtest.h>
#include "Seat.h"

using namespace std;

class SeatTest : public ::testing::Test {
protected:
    Seat* seat;

    void SetUp() override {
        seat = new Seat("12A", false, true, SeatClassType::Economy);
    }

    void TearDown() override {
        delete seat;
    }
};

TEST_F(SeatTest, ConstructorInitializesValuesCorrectly) {
    EXPECT_EQ(seat->getSeatNumber(), "12A");
    EXPECT_FALSE(seat->isOccupiedStatus());
    EXPECT_TRUE(seat->isAvailableStatus());
    EXPECT_EQ(seat->getType(), SeatClassType::Economy);
}

TEST_F(SeatTest, SettersWorkCorrectly) {
    seat->setSeatNumber("1B");
    seat->setOccupied(true);
    seat->setAvailable(false);
    seat->setType(SeatClassType::Business);

    EXPECT_EQ(seat->getSeatNumber(), "1B");
    EXPECT_TRUE(seat->isOccupiedStatus());
    EXPECT_FALSE(seat->isAvailableStatus());
    EXPECT_EQ(seat->getType(), SeatClassType::Business);
}

TEST_F(SeatTest, ReserveMarksSeatAsOccupiedAndUnavailable) {
    seat->reserve();

    EXPECT_TRUE(seat->isOccupiedStatus());
    EXPECT_FALSE(seat->isAvailableStatus());
}

TEST_F(SeatTest, ReserveDoesNothingIfAlreadyUnavailable) {
    seat->setAvailable(false);
    seat->setOccupied(false);
    seat->reserve();

    EXPECT_FALSE(seat->isOccupiedStatus());
    EXPECT_FALSE(seat->isAvailableStatus());
}

TEST_F(SeatTest, ReleaseMakesSeatAvailableAndUnoccupied) {
    seat->setOccupied(true);
    seat->setAvailable(false);
    seat->release();

    EXPECT_FALSE(seat->isOccupiedStatus());
    EXPECT_TRUE(seat->isAvailableStatus());
}

TEST_F(SeatTest, ReleaseDoesNothingIfSeatAlreadyFree) {
    seat->setOccupied(false);
    seat->setAvailable(true);
    seat->release();

    EXPECT_FALSE(seat->isOccupiedStatus());
    EXPECT_TRUE(seat->isAvailableStatus());
}
