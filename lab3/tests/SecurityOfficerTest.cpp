#include <gtest/gtest.h>
#include "SecurityOfficer.h"

TEST(SecurityOfficerTest, ConstructorAndGettersWorkCorrectly) {
    ContactInfo contact("security.ivan@mail.ru", "+79990001122", "Москва");
    SecurityOfficer officer("Иван", "Никитин", time(nullptr),
        contact, 150000.0, true,
        "SEC123", "B12", "Высокий");

    EXPECT_EQ(officer.getName(), "Иван");
    EXPECT_EQ(officer.getSurname(), "Никитин");
    EXPECT_EQ(officer.getBadgeId(), "SEC123");
    EXPECT_EQ(officer.getAssignedGate(), "B12");
    EXPECT_EQ(officer.getClearanceLevel(), "Высокий");
    EXPECT_TRUE(officer.getIsAvailable());
    EXPECT_DOUBLE_EQ(officer.getSalary(), 150000.0);
}

TEST(SecurityOfficerTest, SettersModifyDataCorrectly) {
    ContactInfo contact("olga.kuznetsova@mail.ru", "+79995554411", "Санкт-Петербург");
    SecurityOfficer officer("Ольга", "Кузнецова", time(nullptr),
        contact, 145000.0, false,
        "SEC999", "C5", "Средний");

    officer.setBadgeId("SEC1001");
    officer.setAssignedGate("A7");
    officer.setClearanceLevel("Максимальный");
    officer.setIsAvailable(true);
    officer.setSalary(160000.0);

    EXPECT_EQ(officer.getBadgeId(), "SEC1001");
    EXPECT_EQ(officer.getAssignedGate(), "A7");
    EXPECT_EQ(officer.getClearanceLevel(), "Максимальный");
    EXPECT_TRUE(officer.getIsAvailable());
    EXPECT_DOUBLE_EQ(officer.getSalary(), 160000.0);
}

TEST(SecurityOfficerTest, InspectPassengerReturnsTrue) {
    ContactInfo contactOfficer("andrey.belov@mail.ru", "+79998887766", "Казань");
    SecurityOfficer officer("Андрей", "Белов", time(nullptr),
        contactOfficer, 155000.0, true,
        "SEC777", "D3", "Высокий");

    Visa visa("RUS001", "Франция", time(nullptr), time(nullptr) + 31536000, VisaType::Tourist);
    Passport passport("AB1234567", "Россия", "Пётр Иванов", time(nullptr),
        time(nullptr) + 31536000, visa, MaritalStatus::Married);
    ContactInfo contactPassenger("petr.ivanov@mail.ru", "+79993334455", "Новосибирск");
    Passenger passenger("Пётр", "Иванов", time(nullptr), contactPassenger, "P001", passport);

    EXPECT_TRUE(officer.inspectPassenger(passenger));
}

TEST(SecurityOfficerTest, ReportIncidentOutputsCorrectText) {
    testing::internal::CaptureStdout();

    ContactInfo contact("sergey.morozov@mail.ru", "+79992223344", "Самара");
    SecurityOfficer officer("Сергей", "Морозов", time(nullptr),
        contact, 160000.0, true,
        "SEC555", "E1", "Средний");

    officer.reportIncident("Обнаружен подозрительный багаж у пассажира.");

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Сергей Морозов"), std::string::npos);
    EXPECT_NE(output.find("SEC555"), std::string::npos);
    EXPECT_NE(output.find("Обнаружен подозрительный багаж"), std::string::npos);
}
