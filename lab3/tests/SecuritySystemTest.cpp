#include <gtest/gtest.h>
#include "SecuritySystem.h"

TEST(SecuritySystemTest, ConstructorAndGettersWorkCorrectly) {
    ContactInfo contact1("sergey.petrov@mail.ru", "+79991234567", "Москва");
    SecurityOfficer officer1("Сергей", "Петров", time(nullptr),
        contact1, 140000.0, true, "SEC101", "A1", "Высокий");

    ContactInfo contact2("ivan.sidorov@mail.ru", "+79997654321", "Сочи");
    SecurityOfficer officer2("Иван", "Сидоров", time(nullptr),
        contact2, 135000.0, false, "SEC102", "B2", "Средний");

    vector<SecurityOfficer> officers = { officer1, officer2 };

    SecuritySystem system(25, "Начальные логи", "Нет тревог", officers);

    EXPECT_EQ(system.getActiveCameras(), 25);
    EXPECT_EQ(system.getAccessLogs(), "Начальные логи");
    EXPECT_EQ(system.getAlerts(), "Нет тревог");
    EXPECT_EQ(system.getOfficers().size(), 2);
    EXPECT_EQ(system.getOfficers()[0].getName(), "Сергей");
    EXPECT_EQ(system.getOfficers()[1].getBadgeId(), "SEC102");
}

TEST(SecuritySystemTest, SettersModifyDataCorrectly) {
    vector<SecurityOfficer> officers;
    SecuritySystem system(10, "Пусто", "ОК", officers);

    system.setActiveCameras(30);
    system.setAccessLogs("Обновлённые логи");
    system.setAlerts("Новые тревоги");

    ContactInfo contact("anna.kuzmina@mail.ru", "+79990002233", "Екатеринбург");
    SecurityOfficer officer("Анна", "Кузьмина", time(nullptr),
        contact, 150000.0, true, "SEC200", "C3", "Максимальный");
    system.setOfficers({ officer });

    EXPECT_EQ(system.getActiveCameras(), 30);
    EXPECT_EQ(system.getAccessLogs(), "Обновлённые логи");
    EXPECT_EQ(system.getAlerts(), "Новые тревоги");
    EXPECT_EQ(system.getOfficers().size(), 1);
    EXPECT_EQ(system.getOfficers()[0].getSurname(), "Кузьмина");
}

TEST(SecuritySystemTest, AlertOutputsAndUpdatesAlertsCorrectly) {
    vector<SecurityOfficer> officers;
    SecuritySystem system(20, "", "", officers);

    testing::internal::CaptureStdout();
    system.alert("Нарушение на входе №3!");
    string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Нарушение на входе №3!"), string::npos);
    EXPECT_NE(output.find("["), string::npos);

    EXPECT_NE(system.getAlerts().find("Нарушение на входе №3!"), string::npos);
    EXPECT_NE(system.getAlerts().find("["), string::npos);
}

TEST(SecuritySystemTest, FlagSuspiciousActivityWorksCorrectly) {
    vector<SecurityOfficer> officers;
    SecuritySystem system(15, "", "", officers);

    testing::internal::CaptureStdout();
    system.flagSuspiciousActivity("Неопознанный объект в зоне C1");
    string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Неопознанный объект в зоне C1"), string::npos);
    EXPECT_NE(output.find("["), string::npos);

    EXPECT_NE(system.getAlerts().find("Неопознанный объект в зоне C1"), string::npos);
    EXPECT_NE(system.getAlerts().find("["), string::npos);
}