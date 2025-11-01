#include <gtest/gtest.h>
#include "Shift.h"

class ShiftTest : public ::testing::Test {
protected:
    ContactInfo* contact;  Employee* employee; Shift* shift;
    time_t birthDate; time_t startTime; time_t endTime;

    void SetUp() override {
        birthDate = time(nullptr) - 86400 * 365 * 30;
        contact = new ContactInfo("emp@mail.com", "+79001112233", "Москва, Россия");
        employee = new Employee("Иван", "Петров", birthDate, *contact, 75000.0, true);

        startTime = time(nullptr) - 3600 * 5;
        endTime = time(nullptr);
        shift = new Shift(*employee, startTime, endTime, false);
    }

    void TearDown() override {
        delete contact; delete employee; delete shift;
    }
};

TEST_F(ShiftTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(shift->getEmployee().getName(), "Иван");
    EXPECT_EQ(shift->getEmployee().getSurname(), "Петров");
    EXPECT_DOUBLE_EQ(shift->getEmployee().getSalary(), 75000.0);
    EXPECT_EQ(shift->getStartTime(), startTime);
    EXPECT_EQ(shift->getEndTime(), endTime);
    EXPECT_FALSE(shift->getIsActive());
}

TEST_F(ShiftTest, SettersWorkCorrectly) {
    Employee newEmp("Анна", "Сидорова", birthDate, *contact, 82000.0, false);
    time_t newStart = time(nullptr) - 7200;
    time_t newEnd = time(nullptr);
    shift->setEmployee(newEmp);
    shift->setStartTime(newStart);
    shift->setEndTime(newEnd);
    shift->setActive(true);

    EXPECT_EQ(shift->getEmployee().getName(), "Анна");
    EXPECT_DOUBLE_EQ(shift->getEmployee().getSalary(), 82000.0);
    EXPECT_EQ(shift->getStartTime(), newStart);
    EXPECT_EQ(shift->getEndTime(), newEnd);
    EXPECT_TRUE(shift->getIsActive());
}

TEST_F(ShiftTest, StartShiftActivatesAndSetsStartTime) {
    shift->startShift();
    EXPECT_TRUE(shift->getIsActive());
    EXPECT_NEAR(difftime(time(nullptr), shift->getStartTime()), 0, 2);
}

TEST_F(ShiftTest, EndShiftDeactivatesAndSetsEndTime) {
    shift->startShift();
    shift->endShift();
    EXPECT_FALSE(shift->getIsActive());
    EXPECT_NEAR(difftime(time(nullptr), shift->getEndTime()), 0, 2);
}

TEST_F(ShiftTest, GetDurationHoursCalculatesCorrectly) {
    double duration = shift->getDurationHours();
    EXPECT_NEAR(duration, 5.0, 0.05); 
}

TEST_F(ShiftTest, GetDurationHoursReturnsZeroIfEndBeforeStart) {
    shift->setStartTime(time(nullptr));
    shift->setEndTime(time(nullptr) - 3600);
    EXPECT_DOUBLE_EQ(shift->getDurationHours(), 0.0);
}

TEST_F(ShiftTest, IsOngoingReturnsTrueIfActive) {
    shift->setActive(true);
    EXPECT_TRUE(shift->isOngoing());
}

TEST_F(ShiftTest, IsOngoingReturnsFalseIfInactive) {
    shift->setActive(false);
    EXPECT_FALSE(shift->isOngoing());
}
