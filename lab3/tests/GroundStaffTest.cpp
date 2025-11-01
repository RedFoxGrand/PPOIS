#include <gtest/gtest.h>
#include "GroundStaff.h"

static GroundStaff createTestGroundStaff() {
    time_t now = time(nullptr);
    ContactInfo info = { "staff@example.com", "+123456789", "123 Airport St" };
    Gate gate("G12", false, "");
    GroundStaff staff("Alice", "Brown", now - 60 * 60 * 24 * 365 * 25, info,
        3500.0, true, gate, "Baggage", true);
    return staff;
}

TEST(GroundStaffTest, ConstructorInitializesAllFields) {
    time_t now = time(nullptr);
    ContactInfo info = { "worker@airport.com", "+987654321", "Airport Ave 45" };
    Gate gate("A5", false, "FL123");

    GroundStaff staff("Bob", "Smith", now - 60 * 60 * 24 * 365 * 30,
        info, 4000.0, true, gate, "Security", true);

    EXPECT_EQ(staff.getName(), "Bob");
    EXPECT_EQ(staff.getSurname(), "Smith");
    EXPECT_EQ(staff.getArea(), "Security");
    EXPECT_TRUE(staff.isOnDuty());
    EXPECT_TRUE(staff.getIsAvailable());
    EXPECT_DOUBLE_EQ(staff.getSalary(), 4000.0);
    EXPECT_EQ(staff.getAssignedGate().getGateNumber(), "A5");
}

TEST(GroundStaffTest, SettersWorkCorrectly) {
    GroundStaff staff = createTestGroundStaff();

    Gate newGate("B3", true, "FL789");
    staff.setAssignedGate(newGate);
    staff.setArea("Cleaning");
    staff.setOnDuty(false);
    staff.setSalary(5000.0);
    staff.setIsAvailable(false);

    EXPECT_EQ(staff.getAssignedGate().getGateNumber(), "B3");
    EXPECT_EQ(staff.getAssignedGate().getAssignedFlightNumber(), "FL789");
    EXPECT_EQ(staff.getArea(), "Cleaning");
    EXPECT_FALSE(staff.isOnDuty());
    EXPECT_DOUBLE_EQ(staff.getSalary(), 5000.0);
    EXPECT_FALSE(staff.getIsAvailable());
}

TEST(GroundStaffTest, InheritsFromPersonAndEmployeeCorrectly) {
    GroundStaff staff = createTestGroundStaff();

    EXPECT_EQ(staff.getFullName(), "Alice Brown");
    EXPECT_GT(staff.getAge(), 20);
    EXPECT_TRUE(staff.getIsAvailable());
    EXPECT_GT(staff.getSalary(), 0.0);
}

TEST(GroundStaffTest, CanUpdateAssignedGate) {
    GroundStaff staff = createTestGroundStaff();

    Gate newGate("Z1", false, "");
    staff.setAssignedGate(newGate);
    EXPECT_EQ(staff.getAssignedGate().getGateNumber(), "Z1");

    Gate gate = staff.getAssignedGate();
    gate.assignFlight("FL999");
    EXPECT_TRUE(gate.getIsOccupied());
}
