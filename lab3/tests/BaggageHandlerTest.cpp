#include <gtest/gtest.h>
#include "BaggageHandler.h"

static BaggageHandler createTestHandler() {
    time_t now = time(nullptr);
    ContactInfo info = { "handler@example.com", "+11111111", "Airport Base" };
    Gate gate("H5", false, "");
    return BaggageHandler("John", "Doe", now - 60 * 60 * 24 * 365 * 28, info,
        4200.0, true, gate, "BaggageArea", true, 5);
}

TEST(BaggageHandlerTest, ConstructorInitializesAllFields) {
    time_t now = time(nullptr);
    ContactInfo info = { "staff@airport.com", "+999888777", "Service Point" };
    Gate gate("C7", true, "FL555");

    BaggageHandler handler("Mark", "Taylor", now - 60 * 60 * 24 * 365 * 35,
        info, 4800.0, false, gate, "LoadingZone", false, 10);

    EXPECT_EQ(handler.getName(), "Mark");
    EXPECT_EQ(handler.getSurname(), "Taylor");
    EXPECT_EQ(handler.getFullName(), "Mark Taylor");
    EXPECT_EQ(handler.getArea(), "LoadingZone");
    EXPECT_EQ(handler.getAssignedGate().getGateNumber(), "C7");
    EXPECT_EQ(handler.getExperienceYears(), 10);
    EXPECT_DOUBLE_EQ(handler.getSalary(), 4800.0);
    EXPECT_FALSE(handler.isOnDuty());
    EXPECT_FALSE(handler.getIsAvailable());
}

TEST(BaggageHandlerTest, SettersWorkCorrectly) {
    BaggageHandler handler = createTestHandler();

    handler.setExperienceYears(12);
    handler.setArea("Sorting");
    handler.setOnDuty(false);
    handler.setSalary(5300.0);
    handler.setIsAvailable(false);

    Gate newGate("A1", false, "");
    handler.setAssignedGate(newGate);

    EXPECT_EQ(handler.getExperienceYears(), 12);
    EXPECT_EQ(handler.getArea(), "Sorting");
    EXPECT_FALSE(handler.isOnDuty());
    EXPECT_DOUBLE_EQ(handler.getSalary(), 5300.0);
    EXPECT_FALSE(handler.getIsAvailable());
    EXPECT_EQ(handler.getAssignedGate().getGateNumber(), "A1");
}

TEST(BaggageHandlerTest, InheritanceWorksCorrectly) {
    BaggageHandler handler = createTestHandler();

    EXPECT_EQ(handler.getFullName(), "John Doe");
    EXPECT_GT(handler.getAge(), 20);
    EXPECT_TRUE(handler.getIsAvailable());
    EXPECT_TRUE(handler.isOnDuty());
    EXPECT_GT(handler.getSalary(), 0.0);
}
 
TEST(BaggageHandlerTest, CanUpdateAssignedGate) {
    BaggageHandler handler = createTestHandler();

    Gate newGate("Z9", false, "");
    handler.setAssignedGate(newGate);
    EXPECT_EQ(handler.getAssignedGate().getGateNumber(), "Z9");

    Gate gate = handler.getAssignedGate();
    gate.assignFlight("FL999");
    EXPECT_TRUE(gate.getIsOccupied());
}

TEST(BaggageHandlerTest, ExperienceYearsCanBeChanged) {
    BaggageHandler handler = createTestHandler();
    EXPECT_EQ(handler.getExperienceYears(), 5);

    handler.setExperienceYears(8);
    EXPECT_EQ(handler.getExperienceYears(), 8);
}
