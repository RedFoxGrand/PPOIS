#include <gtest/gtest.h>
#include "AircraftMaintenanceSystem.h"

class AircraftMaintenanceSystemTest : public ::testing::Test {
protected:
    AircraftModel* model1; AircraftModel* model2; Aircraft* aircraft1; Aircraft* aircraft2;
    MaintenanceLog* log1; MaintenanceLog* log2; AircraftMaintenanceSystem* system; time_t now;

    void SetUp() override {
        now = time(nullptr);

        model1 = new AircraftModel("Сухой Суперджет 100", 98, "ГСС", 3000, 2000, "SaM146", 820);
        model2 = new AircraftModel("МС-21", 180, "Иркут", 6000, 2700, "ПД-14", 870);

        aircraft1 = new Aircraft("RA-89001", *model1, 2000, AircraftStatus::Available, true);
        aircraft2 = new Aircraft("RA-73055", *model2, 2500, AircraftStatus::Available, true);

        log1 = new MaintenanceLog("LOG-001", *aircraft1, "Плановая проверка шасси", now - 86400);
        log2 = new MaintenanceLog("LOG-002", *aircraft2, "Замена тормозных дисков", now - 172800);

        vector<Aircraft> aircrafts = { *aircraft1, *aircraft2 };
        vector<MaintenanceLog> logs = { *log1, *log2 };

        system = new AircraftMaintenanceSystem(aircrafts, logs);
    }

    void TearDown() override {
        delete model1; delete model2; delete aircraft1; delete aircraft2;
        delete log1; delete log2; delete system;
    }
};

TEST_F(AircraftMaintenanceSystemTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(system->getAircrafts().size(), 2);
    EXPECT_EQ(system->getLogs().size(), 2);
    EXPECT_EQ(system->getAircrafts()[0].getTailNumber(), "RA-89001");
    EXPECT_EQ(system->getLogs()[1].getDescription(), "Замена тормозных дисков");
}

TEST_F(AircraftMaintenanceSystemTest, SettersWorkCorrectly) {
    AircraftModel newModel("Ил-96", 300, "Ильюшин", 5000, 3200, "ПС-90А", 850);
    Aircraft newAircraft("RA-96100", newModel, 2700, AircraftStatus::Available, true);
    MaintenanceLog newLog("LOG-777", newAircraft, "Проверка топливной системы", now);

    vector<Aircraft> newAircrafts = { newAircraft };
    vector<MaintenanceLog> newLogs = { newLog };

    system->setAircrafts(newAircrafts);
    system->setLogs(newLogs);

    EXPECT_EQ(system->getAircrafts().size(), 1);
    EXPECT_EQ(system->getLogs().size(), 1);
    EXPECT_EQ(system->getAircrafts()[0].getTailNumber(), "RA-96100");
    EXPECT_EQ(system->getLogs()[0].getDescription(), "Проверка топливной системы");
}

TEST_F(AircraftMaintenanceSystemTest, ScheduleCheckChangesStatusAndAddsLog) {
    EXPECT_EQ(aircraft1->getStatus(), AircraftStatus::Available);

    system->scheduleCheck(*aircraft1);

    EXPECT_EQ(aircraft1->getStatus(), AircraftStatus::UnderMaintenance);
    EXPECT_FALSE(aircraft1->getIsAvailable());
    EXPECT_GE(system->getLogs().size(), 3);
}

TEST_F(AircraftMaintenanceSystemTest, GetMaintenanceHistoryReturnsCorrectLogs) {
    system->recordMaintenance(*aircraft1);
    system->recordMaintenance(*aircraft2);
    system->recordMaintenance(*aircraft1);

    vector<MaintenanceLog> history = system->getMaintenanceHistory(*aircraft1);

    EXPECT_GE(history.size(), 2);
    for (const auto& log : history) {
        EXPECT_EQ(log.getAircraft().getTailNumber(), "RA-89001");
    }
}
