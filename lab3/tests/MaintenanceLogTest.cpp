#include <gtest/gtest.h>
#include "MaintenanceLog.h"

class MaintenanceLogTest : public ::testing::Test {
protected:
    AircraftModel* model; Aircraft* aircraft;
    MaintenanceLog* logEntry; time_t date;

    void SetUp() override {
        model = new AircraftModel("Ту-204", 210, "Туполев", 4200, 2500, "ПС-90", 850);
        aircraft = new Aircraft("RA-64055", *model, 3000, AircraftStatus::Available, true);
        date = time(nullptr);
        logEntry = new MaintenanceLog("LOG001", *aircraft, "Плановое техническое обслуживание", date);
    }

    void TearDown() override {
        delete model; delete aircraft; delete logEntry;
    }
};

TEST_F(MaintenanceLogTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(logEntry->getRecordId(), "LOG001");
    EXPECT_EQ(logEntry->getAircraft().getTailNumber(), "RA-64055");
    EXPECT_EQ(logEntry->getDescription(), "Плановое техническое обслуживание");
    EXPECT_LE(abs(difftime(logEntry->getDate(), date)), 1.0); 
}

TEST_F(MaintenanceLogTest, SettersWorkCorrectly) {
    AircraftModel newModel("Ил-96", 300, "Ильюшин", 4500, 2800, "ПС-90А", 870);
    Aircraft newAircraft("RA-96101", newModel, 2500, AircraftStatus::UnderMaintenance, false);

    time_t newDate = time(nullptr) - 86400;
    logEntry->setRecordId("LOG777");
    logEntry->setAircraft(newAircraft);
    logEntry->setDescription("Замена тормозных колодок");
    logEntry->setDate(newDate);

    EXPECT_EQ(logEntry->getRecordId(), "LOG777");
    EXPECT_EQ(logEntry->getAircraft().getTailNumber(), "RA-96101");
    EXPECT_EQ(logEntry->getDescription(), "Замена тормозных колодок");
    EXPECT_EQ(logEntry->getDate(), newDate);
}

TEST_F(MaintenanceLogTest, AddEntryAppendsNewTextCorrectly) {
    logEntry->addEntry("Проверка гидросистемы завершена");
    string desc = logEntry->getDescription();

    EXPECT_NE(desc.find("Проверка гидросистемы завершена"), string::npos);
}
