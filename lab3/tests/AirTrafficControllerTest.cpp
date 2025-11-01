#include <gtest/gtest.h>
#include "AirTrafficController.h"

static AirTrafficController createTestController() {
    time_t now = time(nullptr);
    ContactInfo info = { "controller@atc.com", "+777000999", "Башня 1" };
    return AirTrafficController("Анна", "Петрова", now - 60 * 60 * 24 * 365 * 32,
        info, 7200.0, true, "ATC01", "Зона A");
}

TEST(AirTrafficControllerTest, ConstructorInitializesAllFields) {
    time_t now = time(nullptr);
    ContactInfo info = { "ivanov@control.ru", "+79998887766", "Главаная башня" };

    AirTrafficController controller("Иван", "Иванов", now - 60 * 60 * 24 * 365 * 45,
        info, 8500.0, false, "MSK-TWR", "Зона B");

    EXPECT_EQ(controller.getName(), "Иван");
    EXPECT_EQ(controller.getSurname(), "Иванов");
    EXPECT_EQ(controller.getFullName(), "Иван Иванов");
    EXPECT_EQ(controller.getStationCode(), "MSK-TWR");
    EXPECT_EQ(controller.getControlZone(), "Зона B");
    EXPECT_DOUBLE_EQ(controller.getSalary(), 8500.0);
    EXPECT_FALSE(controller.getIsAvailable());
}

TEST(AirTrafficControllerTest, SettersWorkCorrectly) {
    AirTrafficController controller = createTestController();

    controller.setSalary(9100.0);
    controller.setIsAvailable(false);
    controller.setStationCode("SPB-TWR");
    controller.setControlZone("Зона C");

    EXPECT_DOUBLE_EQ(controller.getSalary(), 9100.0);
    EXPECT_FALSE(controller.getIsAvailable());
    EXPECT_EQ(controller.getStationCode(), "SPB-TWR");
    EXPECT_EQ(controller.getControlZone(), "Зона C");
}

TEST(AirTrafficControllerTest, InheritanceFromEmployeeAndPerson) {
    AirTrafficController controller = createTestController();

    EXPECT_EQ(controller.getFullName(), "Анна Петрова");
    EXPECT_GT(controller.getAge(), 25);
    EXPECT_TRUE(controller.getIsAvailable());
    EXPECT_GT(controller.getSalary(), 0.0);
}

TEST(AirTrafficControllerTest, CanModifyPersonalData) {
    AirTrafficController controller = createTestController();

    controller.setName("Елена");
    controller.setSurname("Морозова");

    EXPECT_EQ(controller.getName(), "Елена");
    EXPECT_EQ(controller.getSurname(), "Морозова");
    EXPECT_EQ(controller.getFullName(), "Елена Морозова");
}

TEST(AirTrafficControllerTest, ControlZoneAndStationCodeAreIndependent) {
    AirTrafficController controller = createTestController();

    controller.setStationCode("ATC77");
    controller.setControlZone("Зона X");

    EXPECT_EQ(controller.getStationCode(), "ATC77");
    EXPECT_EQ(controller.getControlZone(), "Зона X");

    controller.setControlZone("Зона Y");
    EXPECT_EQ(controller.getControlZone(), "Зона Y");
}
