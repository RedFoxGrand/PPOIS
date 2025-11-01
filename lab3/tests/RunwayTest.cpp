#include <gtest/gtest.h>
#include "Runway.h"

TEST(RunwayTest, ConstructorAndGettersWorkCorrectly) {
    Runway runway("RW12", true, 3500.5, RunwayStatus::Available);

    EXPECT_EQ(runway.getCode(), "RW12");
    EXPECT_TRUE(runway.getIsAvailable());
    EXPECT_DOUBLE_EQ(runway.getLength(), 3500.5);
    EXPECT_EQ(runway.getStatus(), RunwayStatus::Available);
}

TEST(RunwayTest, SettersModifyDataCorrectly) {
    Runway runway("RW01", false, 2000.0, RunwayStatus::Closed);

    runway.setCode("RW09");
    runway.setIsAvailable(true);
    runway.setLength(4000.0);
    runway.setStatus(RunwayStatus::UnderMaintenance);

    EXPECT_EQ(runway.getCode(), "RW09");
    EXPECT_TRUE(runway.getIsAvailable());
    EXPECT_DOUBLE_EQ(runway.getLength(), 4000.0);
    EXPECT_EQ(runway.getStatus(), RunwayStatus::UnderMaintenance);
}

TEST(RunwayTest, ReserveRunwayChangesStatusCorrectly) {
    Runway runway("RW07", true, 3000.0, RunwayStatus::Available);

    runway.reserveRunway();

    EXPECT_EQ(runway.getStatus(), RunwayStatus::Reserved);
    EXPECT_FALSE(runway.getIsAvailable());
}

TEST(RunwayTest, ReserveRunwayDoesNothingIfUnavailable) {
    Runway runway("RW05", false, 2500.0, RunwayStatus::Closed);

    runway.reserveRunway();

    EXPECT_EQ(runway.getStatus(), RunwayStatus::Closed);
    EXPECT_FALSE(runway.getIsAvailable());
}

TEST(RunwayTest, ReleaseRunwaySetsAvailableCorrectly) {
    Runway runway("RW03", false, 2200.0, RunwayStatus::Occupied);

    runway.releaseRunway();

    EXPECT_EQ(runway.getStatus(), RunwayStatus::Available);
    EXPECT_TRUE(runway.getIsAvailable());
}

TEST(RunwayTest, ScheduleTakeoffCreatesValidSchedule) {
    Runway runway("RW10", true, 3700.0, RunwayStatus::Available);

    Schedule schedule = runway.scheduleTakeoff("SU123");

    EXPECT_FALSE(runway.getIsAvailable());
    EXPECT_EQ(runway.getStatus(), RunwayStatus::Occupied);

    EXPECT_EQ(schedule.getFlightNumbers().size(), 1);
    EXPECT_EQ(schedule.getFlightNumbers()[0], "SU123");
    EXPECT_FALSE(schedule.getIsRecurring());
}

TEST(RunwayTest, ScheduleLandingCreatesValidSchedule) {
    Runway runway("RW15", true, 3800.0, RunwayStatus::Available);

    Schedule schedule = runway.scheduleLanding("AF456");

    EXPECT_FALSE(runway.getIsAvailable());
    EXPECT_EQ(runway.getStatus(), RunwayStatus::Occupied);

    EXPECT_EQ(schedule.getFlightNumbers().size(), 1);
    EXPECT_EQ(schedule.getFlightNumbers()[0], "AF456");
}
