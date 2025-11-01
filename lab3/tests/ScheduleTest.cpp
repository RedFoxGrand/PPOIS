#include <gtest/gtest.h>
#include "Schedule.h"

using namespace std;

class ScheduleTest : public ::testing::Test {
protected:
    Schedule* schedule; time_t now; time_t future; time_t past;

    void SetUp() override {
        now = time(nullptr);
        future = now + 3600;
        past = now - 3600;

        vector<string> flights = { "SU101", "LH202", "AF303" };
        schedule = new Schedule(flights, now, future, future + 7200, now, false);
    }

    void TearDown() override {
        delete schedule;
    }
};

TEST_F(ScheduleTest, ConstructorInitializesValuesCorrectly) {
    vector<string> expected = { "SU101", "LH202", "AF303" };
    EXPECT_EQ(schedule->getFlightNumbers(), expected);
    EXPECT_EQ(schedule->getLastUpdate(), now);
    EXPECT_EQ(schedule->getDepartureTime(), future);
    EXPECT_EQ(schedule->getArrivalTime(), future + 7200);
    EXPECT_EQ(schedule->getDate(), now);
    EXPECT_FALSE(schedule->getIsRecurring());
}

TEST_F(ScheduleTest, SettersUpdateValuesCorrectly) {
    vector<string> newFlights = { "BA404", "KL505" };
    schedule->setFlightNumbers(newFlights);
    schedule->setLastUpdate(future);
    schedule->setDepartureTime(past);
    schedule->setArrivalTime(future);
    schedule->setDate(future);
    schedule->setIsRecurring(true);

    EXPECT_EQ(schedule->getFlightNumbers(), newFlights);
    EXPECT_EQ(schedule->getLastUpdate(), future);
    EXPECT_EQ(schedule->getDepartureTime(), past);
    EXPECT_EQ(schedule->getArrivalTime(), future);
    EXPECT_EQ(schedule->getDate(), future);
    EXPECT_TRUE(schedule->getIsRecurring());
}

TEST_F(ScheduleTest, AddFlightAddsNewFlightAndUpdatesTime) {
    time_t before = schedule->getLastUpdate();
    schedule->addFlight("QR606");

    EXPECT_GE(schedule->getLastUpdate(), before);
    EXPECT_NE(find(schedule->getFlightNumbers().begin(),
        schedule->getFlightNumbers().end(), "QR606"),
        schedule->getFlightNumbers().end());
}

TEST_F(ScheduleTest, AddFlightDoesNotDuplicateExistingFlight) {
    vector<string> before = schedule->getFlightNumbers();
    schedule->addFlight("SU101");
    EXPECT_EQ(schedule->getFlightNumbers(), before);
}

TEST_F(ScheduleTest, RemoveFlightRemovesExistingFlightAndUpdatesTime) {
    schedule->addFlight("QR606");
    time_t before = schedule->getLastUpdate();
    schedule->removeFlight("QR606");

    EXPECT_GE(schedule->getLastUpdate(), before);
    EXPECT_EQ(find(schedule->getFlightNumbers().begin(),
        schedule->getFlightNumbers().end(), "QR606"),
        schedule->getFlightNumbers().end());
}

TEST_F(ScheduleTest, RemoveFlightDoesNothingIfFlightNotFound) {
    vector<string> before = schedule->getFlightNumbers();
    schedule->removeFlight("NON123");
    EXPECT_EQ(schedule->getFlightNumbers(), before);
}

TEST_F(ScheduleTest, FindFlightByNumberReturnsCorrectValue) {
    EXPECT_EQ(schedule->findFlightByNumber("SU101"), "SU101");
}

TEST_F(ScheduleTest, FindFlightByNumberThrowsIfNotFound) {
    EXPECT_THROW(schedule->findFlightByNumber("XX999"), FlightNotFound);
}

TEST_F(ScheduleTest, IsDelayedReturnsTrueIfDepartureTimeInPast) {
    schedule->setDepartureTime(past);
    EXPECT_TRUE(schedule->isDelayed());
}

TEST_F(ScheduleTest, IsDelayedReturnsFalseIfDepartureTimeInFuture) {
    schedule->setDepartureTime(future);
    EXPECT_FALSE(schedule->isDelayed());
}