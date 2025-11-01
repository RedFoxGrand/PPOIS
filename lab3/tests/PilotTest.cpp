#include <gtest/gtest.h>
#include "Pilot.h"

TEST(PilotTest, ConstructorAndGettersWorkCorrectly) {
    ContactInfo contact("pilot.ivan@mail.ru", "+79995550011", "Москва");
    Pilot pilot("Иван", "Соколов", time(nullptr),
        contact, 250000.0, true,
        "RUS12345", 1200);

    EXPECT_EQ(pilot.getName(), "Иван");
    EXPECT_EQ(pilot.getSurname(), "Соколов");
    EXPECT_EQ(pilot.getLicenseNumber(), "RUS12345");
    EXPECT_EQ(pilot.getFlightHours(), 1200);
    EXPECT_TRUE(pilot.getIsAvailable());
    EXPECT_DOUBLE_EQ(pilot.getSalary(), 250000.0);
}

TEST(PilotTest, SettersWorkCorrectly) {
    ContactInfo contact("aleksey.petrov@mail.ru", "+79997773322", "Санкт-Петербург");
    Pilot pilot("Алексей", "Петров", time(nullptr),
        contact, 230000.0, false,
        "LIC9988", 850);

    pilot.setLicenseNumber("LIC10001");
    pilot.setFlightHours(900);
    pilot.setSalary(240000.0);
    pilot.setIsAvailable(true);

    EXPECT_EQ(pilot.getLicenseNumber(), "LIC10001");
    EXPECT_EQ(pilot.getFlightHours(), 900);
    EXPECT_DOUBLE_EQ(pilot.getSalary(), 240000.0);
    EXPECT_TRUE(pilot.getIsAvailable());
}

TEST(PilotTest, UpdateHoursWorksCorrectly) {
    ContactInfo contact("sergey.volkov@mail.ru", "+79998886655", "Екатеринбург");
    Pilot pilot("Сергей", "Волков", time(nullptr),
        contact, 210000.0, true,
        "FLY777", 500);

    pilot.updateHours(250);
    EXPECT_EQ(pilot.getFlightHours(), 750);

    pilot.updateHours(300);
    EXPECT_EQ(pilot.getFlightHours(), 1050);
}

TEST(PilotTest, CertificationCheckWorksCorrectly) {
    ContactInfo contact("andrey.ivanov@mail.ru", "+79995554433", "Казань");
    Pilot pilot("Андрей", "Иванов", time(nullptr),
        contact, 220000.0, true,
        "LIC9999", 950);

    AircraftModel model("Сухой Суперджет 100", 98, "ГСС", 3000.0, 2500.0, "Турбореактивный", 870);

    EXPECT_FALSE(pilot.isCertifiedFor(model));

    pilot.updateHours(100);
    EXPECT_TRUE(pilot.isCertifiedFor(model));
}
