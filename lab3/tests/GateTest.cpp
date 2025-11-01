#include <gtest/gtest.h>
#include "Gate.h"

class GateTest : public ::testing::Test {
protected:
    Gate* gate;

    void SetUp() override {
        gate = new Gate("A12", false, "");
    }

    void TearDown() override {
        delete gate;
    }
};

TEST_F(GateTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(gate->getGateNumber(), "A12");
    EXPECT_FALSE(gate->getIsOccupied());
    EXPECT_EQ(gate->getAssignedFlightNumber(), "");
}

TEST_F(GateTest, SettersAndGettersWorkCorrectly) {
    gate->setGateNumber("B22");
    gate->setIsOccupied(true);
    gate->setAssignedFlightNumber("FL100");

    EXPECT_EQ(gate->getGateNumber(), "B22");
    EXPECT_TRUE(gate->getIsOccupied());
    EXPECT_EQ(gate->getAssignedFlightNumber(), "FL100");
}

TEST_F(GateTest, AssignFlightAssignsIfFree) {
    gate->assignFlight("FL200");
    EXPECT_TRUE(gate->getIsOccupied());
    EXPECT_EQ(gate->getAssignedFlightNumber(), "FL200");
}

TEST_F(GateTest, AssignFlightDoesNothingIfOccupied) {
    gate->setIsOccupied(true);
    gate->setAssignedFlightNumber("FL300");
    gate->assignFlight("FL400");

    EXPECT_EQ(gate->getAssignedFlightNumber(), "FL300");
}

TEST_F(GateTest, FreeGateClearsFlightIfOccupied) {
    gate->assignFlight("FL500");
    gate->freeGate();

    EXPECT_FALSE(gate->getIsOccupied());
    EXPECT_EQ(gate->getAssignedFlightNumber(), "");
}

TEST_F(GateTest, FreeGateDoesNothingIfAlreadyFree) {
    gate->freeGate();
    EXPECT_FALSE(gate->getIsOccupied());
    EXPECT_EQ(gate->getAssignedFlightNumber(), "");
}

TEST_F(GateTest, MarkClosedSetsClosedAndOccupied) {
    gate->markClosed();
    EXPECT_TRUE(gate->getIsOccupied());
    EXPECT_EQ(gate->getAssignedFlightNumber(), "CLOSED");
}

TEST(GateStaticTest, FindFreeGateReturnsFirstFree) {
    vector<Gate> gates = {
        Gate("A1", true, "FL1"),
        Gate("A2", false, ""),
        Gate("A3", false, "")
    };

    Gate freeGate = Gate::findFreeGate(gates);
    EXPECT_EQ(freeGate.getGateNumber(), "A2");
    EXPECT_FALSE(freeGate.getIsOccupied());
}

TEST(GateStaticTest, FindFreeGateReturnsNAIfNoneFree) {
    vector<Gate> gates = {
        Gate("A1", true, "FL1"),
        Gate("A2", true, "FL2")
    };

    Gate freeGate = Gate::findFreeGate(gates);
    EXPECT_EQ(freeGate.getGateNumber(), "N/A");
    EXPECT_TRUE(freeGate.getIsOccupied());
    EXPECT_EQ(freeGate.getAssignedFlightNumber(), "None");
}
